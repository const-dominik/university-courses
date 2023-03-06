import argparse
import requests
import json

def add_book(title, author, release_year):
    data = json.dumps({
        "title": title,
        "year": release_year,
        "author": author
    })
    res = requests.put("http://127.0.0.1:5000/add_book", json=data)
    print(res.json())

def get_book(title, author):
    data = json.dumps({
        "title": title,
        "author": author
    })
    res = requests.post("http://127.0.0.1:5000/get_book", json=data)
    print(res.json())

def get_friend(email):
    data = json.dumps({
        "email": email
    })
    res = requests.post("http://127.0.0.1:5000/get_friend", json=data)
    print(res.json())

def delete_book(title, author):
    data = json.dumps({
        "title": title,
        "author": author
    })
    res = requests.delete("http://127.0.0.1:5000/delete_book", json=data)
    print(res.json())

def lend_book(title, author, email, name):
    data = json.dumps({
        "title": title,
        "author": author,
        "email": email,
        "name": name
    })
    res = requests.post("http://127.0.0.1:5000/lend_book", json=data)
    print(res.json())

def return_book(title, author, email):
    data = json.dumps({
        "title": title,
        "author": author,
        "email": email
    })
    res = requests.post("http://127.0.0.1:5000/return_book", json=data)
    print(res.json())

parser = argparse.ArgumentParser()

parser.add_argument("--dodaj", dest="add", help="Dodaj książkę: --dodaj tytul autor rok_wydania", nargs=3)
parser.add_argument("--wypozycz", dest="wyp", help="Wypożycz książkę: --wypozycz tytul autor email imie", nargs=4)
parser.add_argument("--oddaj", dest="ret", help="Oddaj książkę: --oddaj tytul autor email", nargs=3)
parser.add_argument("--usun", dest="d", help="Usuń książkę: --usun tytul autor", nargs=2)
parser.add_argument("--ksiazka", dest="ks", help="Zobacz książkę: --ksiazka tytul autor", nargs=2)
parser.add_argument("--przyjaciel", dest="fr", help="Zobacz przyjaciela: --przyjaciel email", nargs=1)

args = parser.parse_args()
if args.add:
    add_book(args.add[0], args.add[1], args.add[2])
if args.wyp:
    lend_book(args.wyp[0], args.wyp[1], args.wyp[2], args.wyp[3])
if args.ret:
    return_book(args.ret[0], args.ret[1], args.ret[2])
if args.d:
    delete_book(args.d[0], args.d[1])
if args.ks:
    get_book(args.ks[0], args.ks[1])
if args.fr:
    get_friend(args.fr[0])