// Couleur Tempo d'aujourd'hui et de demain (API gratuite Jour Tempo, données RTE).
// Navigateur ou Node 18+ : node tempo.mjs   — Doc : https://jourtempo.fr/api/
const API = (globalThis.process?.env?.JOURTEMPO_API) || "https://jourtempo.fr/api/v1";

const reponse = await fetch(`${API}/tempo.json`);
if (!reponse.ok) throw new Error(`HTTP ${reponse.status}`);
const tempo = await reponse.json();

// Au-delà de perime_apres, la donnée n'est plus vraie : on affiche « inconnu ».
const perime = new Date(tempo.perime_apres) < new Date();
console.log("Aujourd'hui :", perime ? "inconnu" : tempo.aujourdhui.libelle);
console.log("Demain :", perime ? "inconnu" : tempo.demain.libelle);
console.log("Rouges restants :", tempo.saison.compteurs.rouge.restants);
console.log(tempo.attribution);
