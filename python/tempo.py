"""Couleur Tempo d'aujourd'hui et de demain (API gratuite Jour Tempo, données RTE).
Python 3, sans bibliothèque à installer : python tempo.py — Doc : https://jourtempo.fr/api/"""
import json
import os
import urllib.request
from datetime import datetime, timezone

API = os.environ.get("JOURTEMPO_API", "https://jourtempo.fr/api/v1")

req = urllib.request.Request(f"{API}/tempo.json", headers={"User-Agent": "mon-script-tempo/1.0"})
with urllib.request.urlopen(req, timeout=10) as r:
    tempo = json.load(r)

perime = datetime.fromisoformat(tempo["perime_apres"]) < datetime.now(timezone.utc)
print("Aujourd'hui :", "inconnu" if perime else tempo["aujourdhui"]["libelle"])
print("Demain :", "inconnu" if perime else tempo["demain"]["libelle"])
print("Rouges restants :", tempo["saison"]["compteurs"]["rouge"]["restants"])
print(tempo["attribution"])
