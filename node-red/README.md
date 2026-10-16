# Node-RED: Tempo colour of today and tomorrow

A ready-to-import Node-RED flow that reads the French **Tempo** electricity tariff colour (blue, white, red) from the
free [Jour Tempo API](https://jourtempo.fr/api/) (no key, no account; colours published by RTE).

*Version française plus bas.*

## Import

Menu (top right) > **Import** > paste the content of [`flow.json`](flow.json) > **Import**, then **Deploy**.
Only core nodes are used (inject, http request, catch, function, debug): nothing to install. Written for
Node-RED 3 or later.

## What it does

- Requests `https://jourtempo.fr/api/v1/tempo.json` every **30 minutes** (once 5 s after deploy).
- **Output 1** of the "Tempo colours" function, when the data is usable:

  ```json
  {
    "today": "bleu", "tomorrow": "rouge",
    "today_date": "2026-12-03", "tomorrow_date": "2026-12-04",
    "remaining": { "bleu": 210, "blanc": 40, "rouge": 20 },
    "expires": "2026-12-04T12:00:00+01:00",
    "collected": "2026-12-03T11:02:41+01:00",
    "from_cache": false, "warning": null,
    "attribution": "Couleurs Tempo : RTE, via Jour Tempo (https://jourtempo.fr)"
  }
  ```

  `tomorrow` is `inconnu` until RTE announces it (around 10:30, Paris time).
- **Output 2** when no colour can be trusted (no answer yet, HTTP or network error without previous data, or data
  past its expiry date `perime_apres`): `{"today": "inconnu", "tomorrow": "inconnu", "error": "..."}`.
  **A colour is never guessed.**
- If a request fails, the last good answer is reused until it expires (`from_cache: true`, reason in `warning`).
- A Tempo day runs from 06:00 to 06:00 (Paris time): after 06:00 the colour announced the day before becomes today's.
- The node status shows the current colours.

Connect output 1 to your own nodes, for example a `switch` on `msg.payload.tomorrow == "rouge"` to delay a water
heater or send a notification.

## Terms of use

- One request every 30 minutes is enough; **never more than one request every 10 minutes**.
- If you display the colours publicly: **"Couleurs Tempo : RTE, via Jour Tempo"** with a link to https://jourtempo.fr.
- Jour Tempo is an independent website, neither EDF nor RTE. Full terms: https://jourtempo.fr/api/

Code under the [MIT licence](../LICENSE). Questions: contact@jourtempo.fr

---

## En français

Un flow Node-RED prêt à importer qui lit la **couleur Tempo** d'aujourd'hui et de demain sur l'API gratuite de
[Jour Tempo](https://jourtempo.fr/api/) (sans clé ni compte, couleurs publiées par RTE).

- **Import** : menu > Importer > coller le contenu de `flow.json` > Importer, puis Déployer. Uniquement des nœuds de
  base, rien à installer.
- Une requête toutes les **30 minutes** (jamais moins de 10 minutes entre deux requêtes).
- **Sortie 1** : `msg.payload.today` et `msg.payload.tomorrow` valent `bleu`, `blanc` ou `rouge` (`tomorrow` vaut
  `inconnu` avant l'annonce de RTE, vers 10 h 30), avec les jours restants de la saison et le texte de crédit.
- **Sortie 2** : aucune couleur fiable (pas encore de réponse, erreur sans donnée précédente, ou date `perime_apres`
  dépassée) : les couleurs valent `inconnu`. **Jamais de couleur devinée.**
- En cas d'erreur, la dernière réponse valide sert jusqu'à sa péremption (`from_cache: true`).
- Le jour Tempo va de 6 h à 6 h (heure de Paris).
- Crédit à afficher si les couleurs sont montrées publiquement : **« Couleurs Tempo : RTE, via Jour Tempo »**, avec un
  lien vers https://jourtempo.fr. Jour Tempo est un site indépendant, ni EDF ni RTE.
