#!/bin/sh
# Couleur Tempo d'aujourd'hui et de demain (API gratuite Jour Tempo, données RTE).
# Doc : https://jourtempo.fr/api/
API="${JOURTEMPO_API:-https://jourtempo.fr/api/v1}"

# Sans jq (python3 suffit) :
curl -fsS "$API/tempo.json" | python3 -c "import json,sys; d=json.load(sys.stdin); print('aujourdhui', d['aujourdhui']['code']); print('demain', d['demain']['code'])"

# Avec jq installé :
# curl -fsS "$API/tempo.json" | jq -r '.demain.code'

# Historique (CSV : date,couleur,saison) : nombre de jours rouges depuis 2014
curl -fsS "$API/tempo-historique.csv" | grep -c ',rouge,'
