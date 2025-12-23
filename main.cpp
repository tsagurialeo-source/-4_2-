#include <pqxx/pqxx>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

class Database {
public:
    pqxx::connection* conn;

    Database() {
        try {
            conn = new pqxx::connection("dbname=products_db user=leocaguria");
            if (conn->is_open()) {
                std::cout << "Connected to database!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Connection failed: " << e.what() << std::endl;
        }
    }

    ~Database() {
        delete conn;
    }

    void log(const std::string& msg) {
        std::ofstream logfile("log.txt", std::ios::app);
        logfile << msg << std::endl;
    }
};

class Category {
protected:
    Database db;
public:
    void add(const std::string& name) {
        try {
            pqxx::work txn(*db.conn);
            txn.exec("INSERT INTO categories (category_name) VALUES (" + txn.quote(name) + ")");
            txn.commit();
            db.log("Added category: " + name);
            std::cout << "Category added: " << name << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};

class Sale {
    Database db;
public:
    void topProducts() {
        try {
            pqxx::work txn(*db.conn);
            auto res = txn.exec("SELECT p.name, COALESCE(SUM(s.quantity_sold), 0) AS total "
                                "FROM products p LEFT JOIN sales s ON p.id = s.product_id "
                                "GROUP BY p.id, p.name ORDER BY total DESC LIMIT 5");
            std::cout << "Top 5 products:\n";
            for (const auto& row : res) {
                std::cout << "Product: " << row["name"].c_str()
                          << ", Sold: " << row["total"].as<int>() << std::endl;
            }
            db.log("Top products queried");
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};

int main() {
    Database db;

    Category cat;
    cat.add("Electronics");

    Sale sale;
    sale.topProducts();

    return 0;
}
