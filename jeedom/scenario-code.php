// Bloc « Code » d'un scénario Jeedom : couleur Tempo (API gratuite Jour Tempo, données RTE).
// Doc : https://jourtempo.fr/api/ — voir README.md pour le virtuel et la programmation.
$json = @file_get_contents('https://jourtempo.fr/api/v1/tempo.json');
$tempo = $json ? json_decode($json, true) : null;
if (!is_array($tempo) || !isset($tempo['demain']['code'])) {
  $scenario->setLog('Jour Tempo : pas de réponse, valeurs gardées');
  return;
}
cmd::byString('#[Maison][Tempo][Aujourdhui]#')->event($tempo['aujourdhui']['code']);
cmd::byString('#[Maison][Tempo][Demain]#')->event($tempo['demain']['code']);
$scenario->setLog('Jour Tempo : aujourd\'hui ' . $tempo['aujourdhui']['code'] . ', demain ' . $tempo['demain']['code']);
