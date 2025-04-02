class Product:
    def __init__(self, product_id, name, price, image, category, manufacturer, status):
        pass


class Image:
    def __init__(self, url_or_path, alt_text):
        pass


class User:
    def __init__(self, user_id, username, email, password, role="User"):
        pass


class Order:
    def __init__(self, order_id, user, products, total_price, status):
        pass


class Admin:
    def __init__(self, admin_id, username, email, password, role="Admin"):
        pass


# Aggregates


class ProductAggregate:
    def add_product(self, product):
        pass

    def edit_product(self, product):
        pass

    def delete_product(self, product):
        pass

    def add_to_cart(self, product):
        pass


class OrderAggregate:
    def create_order(self, user, products):
        pass

    def complete_order(self, order):
        pass

    def pay_order(self, order):
        pass


class UserAggregate:
    def register_user(self, username, email, password):
        pass

    def update_user_info(self, user, new_user):
        pass

    def delete_user(self, user):
        pass


class AdminAggregate:
    def register_admin(self, username, email, password):
        pass

    def add_new_product(self, product):
        pass

    def delete_product(self, product_id):
        pass
