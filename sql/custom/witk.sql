/*
MySQL Data Transfer
Source Host: localhost
Source Database: witk_scriptdev2
Target Host: localhost
Target Database: witk_scriptdev2
Date: 14.09.2015 01:35:56
*/

-- ----------------------------
-- Records 
-- ----------------------------
DELETE FROM `custom_texts` WHERE entry BETWEEN -2006065 AND -2006000;
INSERT INTO `custom_texts` VALUES ('-2006000', 'Who is the Killer starts in %u...', null, null, 'Who is the Killer startet in %u...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006001', 'The game begins...', null, null, 'Das Spiel beginnt...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006002', 'You don\'t have enough free space in your inventory!', null, null, 'Du hast keinen freien Platz in deinem Rucksack!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006003', 'You gained %u gold coins!', null, null, 'Du hast %u Goldmünzen bekommen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006004', 'You gained %u event coins!', null, null, 'Du hast %u Eventmünzen bekommen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006005', 'You gained 1 gold coin!', null, null, 'Du hast 1 Goldmünze bekommen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006006', 'You gained 1 event coin!', null, null, 'Du hast 1 Eventmünze bekommen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006007', '%s has been killed...', null, null, '%s ist gekillt worden...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006008', '%s was defeated...', null, null, '%s ist besiegt worden...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006009', 'You leaved the game zone. You should go back, otherwise you will be teleported in %u sec.', null, null, 'Du hast die Spielzone verlassen. Du solltest umkehren, oder du wirst in %u Sek. teleportiert.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006010', 'You are a killer! Eliminate those pesty campers!', null, null, 'Du bist ein Killer, beseitige diese nervigen Camper!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006011', 'Use the command \".fangen\" to catch a selected camper and then the command \".killen\" to kill him.', null, null, 'Benutze den Befehl \".fangen\" um einen angeklickten Camper zu fangen, und danach den Befehl \".killen\" um ihn zu ermorden.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006012', 'You must wait, until all campers have cast their votes.', null, null, 'Du musst warten, bis alle Camper abgestimmt haben.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006013', 'Your identity has been uncovered!! Get to the teleport rock (see map signal) to escape!', null, null, 'Du wurdest erkannt!! Laufe zum Teleportfelsen (Siehe Kartenmarkierung), um zu entkommen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006014', 'If you hear this sound, then you received a new camper signal on the map.', null, null, 'Wenn du diesen Sound hörst, dann hast du ein neues Signal von einem Camper auf der Karte bekommen.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006015', 'Confuse your victims, so they won\'t know who you are.', null, null, 'Verwirre deine Opfer, sodass sie glauben du bist einer von ihnen.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006016', 'Use the command \".verwirren\" to confuse the camper with your own fake death, or the command \".wechseln\" to camouflage yourself as a camper.', null, null, 'Benutze den Befehl \".verwirren\" um die Camper mit deinem Tot zu verwirren, oder den Befehl \".wechseln\" um dich als Camper zu tarnen.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006017', 'You have %u seconds time to vote!', null, null, 'Du hast %u Sek. Zeit zum Abstimmen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006018', 'The player you voted for was no killer! You lost the game.', null, null, 'Du hast den falschen Spieler für einen Killer gehalten! Damit bist du aus dem Spiel ausgeschieden.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006019', 'You have discovered the identity of a killer! Stop him from getting to the teleport rock (see map signal)!!', null, null, 'Du hast einen Killer erkannt! Er ist jetzt auf dem Weg zum Teleportfelsen (Siehe Kartemarkierung), du musst ihn aufhalten!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006020', 'You are a camper, survive until the timer ends and figure out who is the killer.', null, null, 'Du bist ein Camper, überlebe bis die Zeit abgelaufen ist, und finde heraus wer ein Killer ist.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006021', 'When you hear the scary music, you better run.', null, null, 'Wenn du die gruselige Musik hörst, ist ein Killer nicht weit entfernt von dir.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006022', 'Killers are invisible, but can assume the form of a camper. Don\'t let yourself be fooled!', null, null, 'Killer sind unsichtbar, können aber die Gestalt von einem Camper annehmen, lass dich nicht täuschen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006023', 'All campers are defeated, not bad! You won the game!', null, null, 'Alle Camper wurden besiegt, nicht schlecht! Du hast gewonnen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006024', 'All killers are offline, the game was aborted.', null, null, 'Alle Killer sind offline, das Spiel wurde abgebrochen.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006025', 'You were able to flee through the portal! You won the game!', null, null, 'Du konntest durch das Portal entkommen! Du hast gewonnen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006026', 'All killers are dead! You won the game!', null, null, 'Alle Killer sind tot! Du hast gewonnen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006027', 'There are not enough campers online, the game was aborted.', null, null, 'Es sind nicht mehr genug Camper online, das Spiel wurde abgebrochen.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006028', 'Nobody revealed your identity. You won the game!', null, null, 'Kein Camper hat erkannt wer du wirklich bist. Du hast gewonnen!', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006029', 'You were defeated by a killer...', null, null, 'Ein Killer hat dich besiegt...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006030', 'A killer was able to flee through the portal, you lost the game...', null, null, 'Ein Killer konnte durch das Portal entkommen, du hast leider verloren...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006031', 'You have been killed! You will cause chaos no longer...', null, null, 'Die Camper haben dich umgebracht, du hast leider verloren...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006032', 'The game ended in a tie.', null, null, 'Das Spiel endet unentschieden.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006033', 'Can not be used right now', null, null, 'Kann nicht verwendet werden', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006034', 'You have to selected a killer first', null, null, 'Du musst zuerst einen Killer anklicken', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006035', 'You have to select a camper first', null, null, 'Du musst zuerst einen Camper anklicken', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006036', 'A killer managed it to flee through the portal before you, you lost the game...', null, null, 'Ein Killer hat es vor dir durch das Portal geschafft, du hast leider verloren.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006037', 'The selected player is no camper', null, null, 'Der angeklickte Spieler ist kein Camper', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006038', 'The killer is too far away', null, null, 'Der Killer ist zu weit entfernt', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006039', 'This camper is too far away', null, null, 'Dieser Camper ist zu weit entfernt', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006040', 'This camper has to be caught first', null, null, 'Dieser Camper muss zuerst gefangen werden', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006041', 'This camper was caught already', null, null, 'Dieser Camper wurde bereits gefangen', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006042', 'Your fake camper was already defeated', null, null, 'Dein Fake Camper wurde bereits besiegt', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006043', 'You have to be in the killer form first', null, null, 'Du musst zuerst in der Killerform sein', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006044', 'You can kill the camper in %u seconds', null, null, 'Du kannst den Camper in %u Sekunden killen', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006045', 'You can kill the camper in 1 second', null, null, 'Du kannst den Camper in 1 Sekunde killen', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006046', 'You can kill the camper now', null, null, 'Du kannst den Camper jetzt killen', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006047', 'You already caught a camper, kill this one first.', null, null, 'Du hast bereits einen Camper gefangen, töte zuerst diesen.', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006048', 'The game will be closed in %u seconds...', null, null, 'Das Spiel wird in %u Sekunden geschlossen...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006049', 'The game will be closed in 1 second...', null, null, 'Das Spiel wird in 1 Sekunde geschlossen...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006050', 'The game will be closed in %u minutes...', null, null, 'Das Spiel wird in %u Minuten geschlossen...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006051', 'The game will be closed in 1 minute...', null, null, 'Das Spiel wird in 1 Minute geschlossen...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006052', 'The game will be closed now...', null, null, 'Das Spiel wird jetzt geschlossen...', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006053', '#%u %s', null, null, '#%u %s', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006054', '#%u %s [Kick]', null, null, '#%u %s [Kicken]', null, null, null, null, null, '0', '0', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006055', 'You game name is too long.', null, null, 'Der von dir eingegebene Spielname ist zu lang.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006056', 'There are currently too many games created.', null, null, 'Es wurden schon zuviele Spiele erstellt.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006057', 'The game was already started.', null, null, 'Das Spiel wurde bereits gestartet.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006058', 'The game is full, nobody can join anymore.', null, null, 'Das Spiel ist voll, es kann niemand mehr beitreten.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006059', 'The game could not be started, because there is currently another game running.', null, null, 'Das Spiel konnte nicht gestartet werden, weil gerade ein anderes Spiel läuft.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006060', 'The game could not be started, because there joined too few players.', null, null, 'Das Spiel konnte nicht gestartet werden, weil zuwenige Spieler beigetreten sind.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006061', 'You don\'t have the permission to do that.', null, null, 'Du hast nicht die Rechte das zu tun.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006062', 'You can\'t vote, because you are the killer of course.', null, null, 'Du kannst nicht abstimmen, weil du der Killer bist.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006063', 'You are not registered to this game anymore.', null, null, 'Du bist bei diesem Spiel nicht mehr angemeldet.', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006064', 'You voted!', null, null, 'Du hast abgestimmt!', null, null, null, null, null, '0', '4', '0', '0', null);
INSERT INTO `custom_texts` VALUES ('-2006065', 'This game doesn\'t exists anymore.', null, null, 'Dieses Spiel existiert nicht mehr.', null, null, null, null, null, '0', '4', '0', '0', null);

DELETE FROM `gossip_texts` WHERE entry BETWEEN -3990325 AND -3990300;
INSERT INTO `gossip_texts` VALUES ('-3990300', 'Create Game', null, null, 'Spiel Erstellen', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990301', 'Join Game', null, null, 'Spiel Beitreten', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990302', 'Close', null, null, 'Schließen', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990303', '[Creator][Start Game]', null, null, '[Leiter][Spiel Starten]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990304', '[GM][Start Game]', null, null, '[GM][Spiel Starten]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990305', '[Refresh]', null, null, '[Aktualisieren]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990306', '[Creator][Delete Game]', null, null, '[Leiter][Spiel Entfernen]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990307', '[GM][Delete Game]', null, null, '[GM][Spiel Entfernen]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990308', '[Leave Game]', null, null, '[Spiel Verlassen]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990309', 'Write the name of the game in the following field to create it.', null, null, 'Tippe den Namen des Spiels in das kommende Feld, um das Spiel zu Erstellen.', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990310', '[Creator][Lives: %u][Change]', null, null, '[Leiter][Leben: %u][Ändern]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990311', '[GM][Lives: %u][Change]', null, null, '[GM][Leben: %u][Ändern]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990312', '[Creator][Killer: %u][Change]', null, null, '[Leiter][Killer: %u][Ändern]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990313', '[GM][Killer: %u][Change]', null, null, '[GM][Killer: %u][Ändern]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990314', '[Lives %u]', null, null, '[Leben %u]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990315', '[%u Lives]', null, null, '[%u Leben]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990316', '[Killer %u]', null, null, '[Killer %u]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990317', '[%u Killer]', null, null, '[%u Killer]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990318', '[Kill %u Minutes]', null, null, '[Killen %u Minuten]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990319', '[%u Minutes Kill]', null, null, '[%u Minuten Killen]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990320', '[Escape %u Minutes]', null, null, '[Flucht %u Minuten]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990321', '[%u Minutes Escape]', null, null, '[%u Minuten Flucht]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990322', '[Creator][Kill: %u Minutes][Change]', null, null, '[Leiter][Killen: %u Minuten][Ändern]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990323', '[GM][Kill: %u Minutes][Change]', null, null, '[GM][Killen: %u Minuten][Ändern]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990324', '[Creator][Escape: %u Minutes][Change]', null, null, '[Leiter][Flucht: %u Minuten][Ändern]', null, null, null, null, null, null);
INSERT INTO `gossip_texts` VALUES ('-3990325', '[GM][Escape: %u Minutes][Change]', null, null, '[GM][Flucht: %u Minuten][Ändern]', null, null, null, null, null, null);
