CREATE TABLE categories (
    id SERIAL PRIMARY KEY,
    category_name VARCHAR(100) NOT NULL
);

CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    quantity INTEGER NOT NULL,
    category_id INTEGER REFERENCES categories(id) ON DELETE CASCADE
);

CREATE TABLE sales (
    id SERIAL PRIMARY KEY,
    product_id INTEGER REFERENCES products(id) ON DELETE CASCADE,
    sale_date DATE NOT NULL,
    quantity_sold INTEGER NOT NULL
);
CREATE INDEX idx_categories_name ON categories(category_name);
CREATE INDEX idx_products_name ON products(name);
CREATE INDEX idx_sales_date ON sales(sale_date);
