import requests
from bs4 import BeautifulSoup as bs

visited = []

def get_soup(page):
    r = requests.get(page)
    soup = bs(r.content, "html.parser")
    return soup

def get_link(page, href):
    if "http" in href:
        return href
    if page[-1] == "/":
        return page + href[1:]
    return page + href

def get_links_from_soup(page, soup):
    return list(map(lambda t: get_link(page, t.get("href", "")), soup.find_all("a")))

def crawl(start_page, distance, action):
    if (distance == 0 or start_page in visited): return
    visited.append(start_page)
    soup = get_soup(start_page)
    result = action(soup)
    yield (start_page, result)
    for link in get_links_from_soup(start_page, soup):
        yield from crawl(link, distance - 1, action)


for url, wynik in crawl("https://www.ii.uni.wroc.pl/", 2, lambda tekst : 'Python' in tekst):
    print(url, wynik)