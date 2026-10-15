"""Jours rouges et blancs de chaque saison Tempo depuis 2014, d'après le CSV de Jour Tempo (données RTE).
python historique.py — Doc : https://jourtempo.fr/api/"""
import csv
import io
import os
import urllib.request
from collections import Counter

API = os.environ.get("JOURTEMPO_API", "https://jourtempo.fr/api/v1")

req = urllib.request.Request(f"{API}/tempo-historique.csv", headers={"User-Agent": "mon-script-tempo/1.0"})
texte = urllib.request.urlopen(req, timeout=10).read().decode("utf-8")
compte = Counter((ligne["saison"], ligne["couleur"]) for ligne in csv.DictReader(io.StringIO(texte)))

print("saison     rouges  blancs")
for saison in sorted({s for s, _ in compte}):
    print(f"{saison}  {compte[saison, 'rouge']:6}  {compte[saison, 'blanc']:6}")
