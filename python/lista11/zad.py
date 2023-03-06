import datetime
import re
import argparse
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime, create_engine
from sqlalchemy.orm import relationship, validates, sessionmaker

Base = declarative_base()

class Author(Base):
    __tablename__ = "Autorzy"
    id = Column(Integer, primary_key=True)
    name = Column(String)
    number_of_books = Column(Integer)
    books = relationship("Book")

    @validates("number_of_books")
    def validate_num_of_books(self, key, value):
        assert value > 0

class Friend(Base):
    __tablename__ = "Znajomi"
    id = Column(Integer, primary_key=True)
    name = Column(String(20))
    email = Column(String)
    books = relationship("Book")

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

    @validates("release_year")
    def validate_release_year(self, key, value):
        assert value <= int(datetime.datetime.now().strftime("%Y"))
        return value

engine = create_engine("sqlite:///wyklad.db", echo=True)
Session = sessionmaker(bind=engine)
sesja = Session()
Base.metadata.create_all(engine)

def add_book(title, release, author):
    book = Book(title=title, release_year=release, author=author)
    sesja.add(book)
    sesja.commit()
    print("Książka została dodana!")

def lend_book(title, email, name):
    books = sesja.query(Book).filter(Book.title == title).all()
    if len(books) == 0:
        print("Nie posiadasz takiej książki.")
        return
    friends = sesja.query(Friend).filter(Friend.email == email).all()
    friend = None
    if len(friends) == 0:
        friend = Friend(email=email, name=name)
        sesja.add(friend)
        print("Przyjaciel utworzony.")
    else:
        friend = friends[0]
        print("Przyjaciel znaleziony.")
    book = books[0]
    if book.borrowed_to == -1 or book.borrowed_to == None:
        friend.books = friend.books.append(book) if friend.books else [book]
    print("Książka została wypożyczona!")
    sesja.commit()

def return_book(title, email):
    books = sesja.query(Book).filter(Book.title == title).all()
    if len(books) == 0:
        print("Książka o tym tytule nie należy do twojej biblioteki.")
        return
    friends = sesja.query(Friend).filter(Friend.email == email).all()
    if len(friends) == 0:
        print("Nie masz takiego przyjaciela. :(")
        return
    book = books[0]
    friend = friends[0]
    print(book.id, friend.books[0].id)
    for book in friend.books:
        if book.title == title:
            friend.books = list(filter(lambda b: b.id != book.id, friend.books))
    print("Książka została zwrócona!")
    sesja.commit()

def get_book(title):
    books = sesja.query(Book).filter(Book.title == title).all()
    if len(books) == 0:
        print("i dont have that book :(")
        return
    print(len(books))
    b = books[0]
    print(b.id, b.title, b.release_year, b.author, b.borrowed_to)

def get_friend(email):
    frs = sesja.query(Friend).filter(Friend.email == email).all()
    if len(frs) == 0:
        print("i dont have that book :(")
        return
    print(len(frs))
    b = frs[0]
    print(b.id, b.email, b.name, b.books)

parser = argparse.ArgumentParser()

parser.add_argument("--dodaj", dest="add", help="Dodaj książkę: --dodaj tytul autor rok_wydania", nargs=3)
parser.add_argument("--wypozycz", dest="wyp", help="Wypożycz książkę: --wypozycz tytul email imie", nargs=3)
parser.add_argument("--oddaj", dest="ret", help="Oddaj książkę: --oddaj tytul email", nargs=2)

args = parser.parse_args()
if args.add:
    add_book(args.add[0], int(args.add[2]), args.add[1])
if args.wyp:
    lend_book(args.wyp[0], args.wyp[1], args.wyp[2])
if args.ret:
    return_book(args.ret[0], args.ret[1])