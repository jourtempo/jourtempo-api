# Jeedom : couleur Tempo dans un virtuel

1. Plugin **Virtuel** : créez un équipement `Tempo` dans l'objet `Maison`, avec deux commandes **info** de sous-type
   *autre* : `Aujourdhui` et `Demain`.
2. Créez un scénario en mode **programmé**, cron `5 6,11,12,13,18 * * *` (6 h 05, 11 h 05, 12 h 05, 13 h 05, 18 h 05).
3. Ajoutez un bloc **Code** et collez le contenu de [`scenario-code.php`](scenario-code.php).
4. Adaptez `#[Maison][Tempo][…]#` si votre objet ou votre équipement porte un autre nom.

Les commandes valent `bleu`, `blanc`, `rouge` (et `inconnu` pour demain avant l'annonce de RTE, vers 10 h 30).
Elles peuvent déclencher vos autres scénarios (`#[Maison][Tempo][Demain]# == "rouge"` → notification, délestage…).

Données : RTE, via [Jour Tempo](https://jourtempo.fr/api/).
