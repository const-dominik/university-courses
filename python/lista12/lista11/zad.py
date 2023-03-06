import flask
import datetime
import re
import json
from flask import Flask, request, jsonify
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime, create_engine
from sqlalchemy.orm import relationship, validates, sessionmaker

app = flask.Flask("library_app")

Base = declarative_base()

class Author(Base):
    __tablename__ = "Autorzy"
    id = Column(Integer, primary_key=True)
    name = Column(String)
    number_of_books = Column(Integer)
    books = relationship("Book")

    def serialize(self):
        return {
            "id": self.id,
            "name": self.name,
            "number_of_books": self.number_of_books,
            "books": list(map(lambda x: x.serialize(), self.books))
        }

    @validates("number_of_books")
    def validate_num_of_books(self, key, value):
        assert value > 0

class Friend(Base):
    __tablename__ = "Znajomi"
    id = Column(Integer, primary_key=True)
    name = Column(String(20))
    email = Column(String)
    books = relationship("Book")

    def serialize(self):
        return {
            "id": self.id,
            "name": self.name,
            "email": self.email,
            "books": list(map(lambda x: x.serialize(), self.books))
        }

    @validates("email")
    def validate_email(self, key, value):
        assert re.search(r"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)", value)
        return value

class Book(Base):
    __tablename__ = "Książki"
    id = Column(Integer, primary_key=True)
    title = Column(String(100), nullable=False)
    release_year = Column(Integer, default=datetime.date.year)
    author = Column(String, ForeignKey("Autorzy.id"), nullable=False)
    borrowed_to = Column(Integer, ForeignKey("Znajomi.id"), default=-1)

    def serialize(self):
        return {
            "id": self.id,
            "title": self.title,
            "release_year": self.release_year,
            "author": self.author,
            "borrowed_to": self.borrowed_to
        }

    @validates("release_year")
    def validate_release_year(self, key, value):
        assert int(value) <= int(datetime.datetime.now().strftime("%Y"))
        return value

engine = create_engine("sqlite:///wyklad.db", echo=True, connect_args={'check_same_thread': False})
Session = sessionmaker(bind=engine)
sesja = Session()
Base.metadata.create_all(engine)

#CREATE
@app.route('/add_book', methods=['PUT'])
def add_book():
    json_data = json.loads(request.get_json())
    title = json_data.get("title")
    release_year = json_data.get("year")
    author = json_data.get("author")
    book = Book(title=title, release_year=release_year, author=author)
    sesja.add(book)
    sesja.commit()
    
    return jsonify({ "msg": "Done!" })

#UPDATE
@app.route('/lend_book', methods=["POST"])
def lend_book():
    json_data = json.loads(request.get_json())
    title = json_data.get("title")
    author = json_data.get("author")
    email = json_data.get("email")
    name = json_data.get("name")
    books = sesja.query(Book).filter(Book.title == title and Book.author == author).all()

    if len(books) == 0:
        return jsonify({ "msg": "You don't have that book." })

    friends = sesja.query(Friend).filter(Friend.email == email).all()
    friend = None

    if len(friends) == 0:
        friend = Friend(email=email, name=name)
        sesja.add(friend)
        
    else:
        friend = friends[0]
        
    book = books[0]

    if book.borrowed_to == -1 or book.borrowed_to == None:
        friend.books = friend.books.append(book) if friend.books else [book]
    
    sesja.commit()

    return jsonify({ "msg": "Done!" })

@app.route('/return_book', methods=["POST"])
def return_book():
    json_data = json.loads(request.get_json())
    
    title = json_data.get("title")
    author = json_data.get("author")
    email = json_data.get("email")

    books = sesja.query(Book).filter(Book.title == title and Book.author == author).all()
    
    if len(books) == 0:
        return jsonify({ "msg": "You don't have that book." })

    friends = sesja.query(Friend).filter(Friend.email == email).all()
    
    if len(friends) == 0:
        return jsonify({ "msg": "You don't have that friend." })
    
    book = books[0]
    friend = friends[0]
    
    for book in friend.books:
        if book.title == title:
            friend.books = list(filter(lambda b: b.id != book.id, friend.books))
    
    sesja.commit()

    return jsonify({ "msg": "Done!" })

#DELETE
@app.route('/delete_book', methods=['DELETE'])
def delete_book():
    json_data = json.loads(request.get_json())
    title = json_data.get("title")
    author = json_data.get("author")

    books = sesja.query(Book).filter(Book.title == title and Book.author == author).all()
    if len(books) == 0:
        return jsonify({ "msg": "You don't have that book." })

    sesja.delete(books[0])
    sesja.commit()
    return jsonify({ "msg": "Done!" })

#READ
@app.route('/get_book', methods=['POST'])
def get_book():
    json_data = json.loads(request.get_json())
    title = json_data.get("title")
    author = json_data.get("author")

    books = sesja.query(Book).filter(Book.title == title and Book.author == author).all()
    
    if len(books) == 0:
        return jsonify({ "msg": "You don't have that book." })
    b = books[0]
    return jsonify(b.serialize())

@app.route('/get_friend', methods=['POST'])
def get_friend():
    json_data = json.loads(request.get_json())
    email = json_data.get("email")
    frs = sesja.query(Friend).filter(Friend.email == email).all()
    if len(frs) == 0:
        return jsonify({ "msg": "You don't have a friend with given email address." })
    b = frs[0]
    return jsonify(b.serialize())

app.run()