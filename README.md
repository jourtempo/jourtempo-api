# Jour Tempo : exemples pour l'API Tempo gratuite

Exemples prêts à copier pour lire la **couleur Tempo d'aujourd'hui et de demain** (bleu, blanc, rouge) et l'**historique
depuis 2014** depuis l'API publique de [Jour Tempo](https://jourtempo.fr/) : sans clé, sans compte, CORS ouvert.

Documentation complète (champs, conditions, comment citer) : **https://jourtempo.fr/api/**

| Adresse | Contenu |
| --- | --- |
| `https://jourtempo.fr/api/v1/tempo.json` | couleur d'aujourd'hui et de demain, jours restants de la saison, calendrier de la saison |
| `https://jourtempo.fr/api/v1/tempo-historique.csv` | une ligne par jour depuis le 1er septembre 2014 : `date,couleur,saison` |
| `https://jourtempo.fr/api/v1/ejp.json` | jour EJP d'aujourd'hui et de demain, compteur des 22 jours |

Les couleurs sont publiées par **RTE** (API Tempo Like Supply Contract) et relevées par Jour Tempo six fois par jour.
`demain.code` vaut `inconnu` tant que RTE n'a pas annoncé la couleur (annonce vers 10 h 30, présente dans l'API en
général avant 13 h). Au-delà de `perime_apres`, considérez la donnée comme inconnue.

## Exemples

| Dossier | Pour |
| --- | --- |
| [`shell/`](shell/) | `curl` dans un terminal |
| [`javascript/`](javascript/) | navigateur ou Node 18+ (`fetch`) |
| [`python/`](python/) | Python 3 sans dépendance, dont le comptage des jours rouges par saison depuis le CSV |
| [`home-assistant/`](home-assistant/) | capteurs REST, capteur binaire « demain rouge », alerte la veille à 18 h |
| [`jeedom/`](jeedom/) | virtuel + bloc code de scénario |
| [`domoticz/`](domoticz/) | script dzVents |
| [`esp32/`](esp32/) | ESP32 + ArduinoJson 7 : une lampe témoin qui prend la couleur du jour |
| [`node-red/`](node-red/) | flow Node-RED prêt à importer : couleur du jour et de demain toutes les 30 min, erreurs et péremption gérées |

Les exemples Home Assistant, Jeedom, Domoticz et ESP32 sont à adapter à votre installation (noms d'entités, broches). Un retour sur votre configuration est le bienvenu.

Google Sheets, sans code : `=IMPORTDATA("https://jourtempo.fr/api/v1/tempo-historique.csv")`, puis par exemple
`=NB.SI.ENS(C:C;"2025-2026";B:B;"rouge")` pour compter les rouges d'une saison.

## Bon usage

- Un appel toutes les **30 minutes** suffit (la couleur change une fois par jour) ; **jamais moins de 10 minutes** entre deux appels.
- Si vous affichez les couleurs publiquement : **« Couleurs Tempo : RTE, via [Jour Tempo](https://jourtempo.fr/) »**.
- Jour Tempo est un site indépendant, ni EDF ni RTE.
- Le format `v1` est stable : les champs ne changeront ni de nom ni de sens.

Une erreur, une idée d'exemple (ESPHome, Homey, Gladys…) ? Ouvrez une *issue* ou écrivez à contact@jourtempo.fr.

## Licence

Code des exemples : [MIT](LICENSE). Les couleurs Tempo sont des données publiées par RTE.
