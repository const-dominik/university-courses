import requests
import urllib.parse
import json
from prywatne import key

def getPublicAPIData(url):
    r = requests.get(url)
    content = json.loads(r.content.decode('utf-8'))
    return content.get("fact")

def getImdbAPIData(key, title):
    encoded_title = urllib.parse.quote(title)
    url = f"https://imdb-api.com/en/API/Search/{key}/${encoded_title}"
    r = requests.get(url)
    content = json.loads(r.content.decode('utf-8'))
    return content.get("results")[0]

print(getPublicAPIData("https://catfact.ninja/fact"))
print(getImdbAPIData(key, "pulp fiction"))
