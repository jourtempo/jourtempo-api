-- Domoticz (dzVents) : couleur Tempo (API gratuite Jour Tempo, données RTE). Doc : https://jourtempo.fr/api/
-- Prérequis : deux capteurs virtuels de type « Texte » (Matériel > Dummy) nommés « Tempo aujourd'hui » et « Tempo demain ».
-- À créer dans Configuration > Plus d'options > Événements > dzVents.
return {
  on = {
    timer = { 'at 06:10', 'at 11:10', 'at 12:10', 'at 13:10', 'at 18:10' },
    httpResponses = { 'jourtempo' }
  },
  logging = { marker = 'jourtempo' },
  execute = function(domoticz, item)
    if item.isTimer then
      domoticz.openURL({ url = 'https://jourtempo.fr/api/v1/tempo.json', method = 'GET', callback = 'jourtempo' })
    elseif item.isHTTPResponse then
      if item.ok and item.isJSON then
        local tempo = item.json
        domoticz.devices("Tempo aujourd'hui").updateText(tempo.aujourdhui.libelle)
        domoticz.devices('Tempo demain').updateText(tempo.demain.libelle)
        domoticz.log('demain ' .. tempo.demain.code, domoticz.LOG_INFO)
      else
        domoticz.log('pas de réponse (' .. tostring(item.statusCode) .. '), valeurs gardées', domoticz.LOG_ERROR)
      end
    end
  end
}
