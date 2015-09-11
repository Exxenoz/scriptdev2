#include "precompiled.h"
#include "WhoIsTheKillerSpiel.h"
#include "WhoIsTheKillerMgr.h"

enum WhoIsTheKillerGossip
{
    GOSSIP_START_HALLO    = 300800,
    GOSSIP_BEIGETRETEN    = 300801,
    GOSSIP_BEITRETEN    = 300802,
    GOSSIP_ANZAHL_LEBEN    = 300803,
    GOSSIP_ABSTIMMEN    = 300804,
    GOSSIP_GRUSS_HALLO    = 300805,
    GOSSIP_ANZAHL_KILLER = 300806,

    GOSSIP_SPIEL_ERSTELLEN = -3990300,
    GOSSIP_SPIEL_BEITRETEN = -3990301,
    GOSSIP_SCHLIESSEN = -3990302,
    GOSSIP_SPIEL_STARTEN_LEITER = -3990303,
    GOSSIP_SPIEL_STARTEN_GM = -3990304,
    GOSSIP_AKTUALISIEREN = -3990305,
    GOSSIP_SPIEL_ENTFERNEN_LEITER = -3990306,
    GOSSIP_SPIEL_ENTFERNEN_GM = -3990307,
    GOSSIP_SPIEL_VERLASSEN = -3990308,
    GOSSIP_SPIEL_NAME_EINGEBEN = -3990309,
    GOSSIP_LEBEN_MOD_LEITER = -3990310,
    GOSSIP_LEBEN_MOD_GM = -3990311,
    GOSSIP_KILLER_MOD_LEITER = -3990312,
    GOSSIP_KILLER_MOD_GM = -3990313,
    GOSSIP_LEBEN_NORMAL = -3990314,
    GOSSIP_LEBEN_AUSWAHL = -3990315,
    GOSSIP_KILLER_NORMAL = -3990316,
    GOSSIP_KILLER_AUSWAHL = -3990317,
    GOSSIP_STATUS_KILLEN_ENDE_NORMAL = -3990318,
    GOSSIP_STATUS_KILLEN_ENDE_AUSWAHL = -3990319,
    GOSSIP_STATUS_FLUCHT_ENDE_NORMAL = -3990320,
    GOSSIP_STATUS_FLUCHT_ENDE_AUSWAHL = -3990321,
    GOSSIP_STATUS_KILLEN_ENDE_MOD_LEITER = -3990322,
    GOSSIP_STATUS_KILLEN_ENDE_MOD_GM = -3990323,
    GOSSIP_STATUS_FLUCHT_ENDE_MOD_LEITER = -3990324,
    GOSSIP_STATUS_FLUCHT_ENDE_MOD_GM = -3990325
};

enum WhoIsTheKillerText
{
    TEXT_SPIELNAME_ZU_LANG = -2006055,
    TEXT_ZUVIELE_SPIELE = -2006056,
    TEXT_SPIEL_SCHON_GESTARTET = -2006057,
    TEXT_SPIEL_VOLL = -2006058,
    TEXT_ANDERES_SPIEL_LAUFT_GERADE = -2006059,
    TEXT_ZU_WENIGE_SPIELER = -2006060,
    TEXT_KEINE_RECHTE = -2006061,
    TEXT_ABSTIMMEN_KILLER = -2006062,
    TEXT_NICHT_MEHR_ANGEMELDET = -2006063,
    TEXT_ABGESTIMMT_CAMPER = -2006064,
    TEXT_SPIEL_EXISTIERT_NICHT_MEHR = -2006065
};

enum WhoIsTheKillerSender
{
    SENDER_MAIN = 1,
    SENDER_SPIELE_LISTE = 2,
    SENDER_SPIELE_LISTE2 = 3,
    SENDER_SPIELER_LISTE = 4,
    SENDER_SPIELER_LISTE2 = 5,
    SENDER_LEBEN = 6,
    SENDER_ABSTIMMEN = 7,
    SENDER_KILLER = 8,
    SENDER_KILLEN_ENDE = 9,
    SENDER_FLUCHT_ENDE = 10
};

enum WhoIsTheKillerAktionen
{
    AKTION_SCHLIESSEN = 0,
    AKTION_SPIEL_ERSTELLEN = 1,
    AKTION_SPIEL_BEITRETEN = 2,
    AKTION_SPIEL_STARTEN = 3,
    AKTION_LEBEN_AUSWAHL = 4,
    AKTION_AKTUALISIEREN = 5,
    AKTION_SPIEL_ENTFERNEN = 6,
    AKTION_SPIEL_VERLASSEN = 7,
    AKTION_KILLER_AUSWAHL = 8,
    AKTION_KILLEN_ENDE_AUSWAHL = 9,
    AKTION_FLUCHT_ENDE_AUSWAHL = 10
};

static const uint32 aStatusKillenEndeAuswahl[] =
{
    60, // 1 Minute <Test>
    360, // 6 Minuten
    480, // 8 Minuten
    600, // 10 Minuten
    900, // 15 Minuten
    1200 // 20 Minuten
};

static const uint32 aStatusFluchtEndeAuswahl[] =
{
    60, // 1 Minute <Test>
    360, // 6 Minuten
    480, // 8 Minuten
    600 // 10 Minuten
};

// Erstellt eine Liste mit den erstellten Spielen
void SpieleListeAnzeigen(Player* pPlayer, Creature* pCreature)
{
    // Die Spieleliste wird erstellt
    sWhoIsTheKillerMgrSD2::ErstelleSpieleListe(pPlayer, 0, SENDER_SPIELE_LISTE2);
    // Aktualisieren
    pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_AKTUALISIEREN, SENDER_SPIELE_LISTE, AKTION_AKTUALISIEREN);

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_BEITRETEN, pCreature->GetObjectGuid());
}

// Erstellt eine Liste der Spieler mit denen man spielt
void SpielerListeAnzeigen(Player* pPlayer, Creature* pCreature, WhoIsTheKillerSpiel* pSpiel)
{
    // Der Leiter ist in der Lage das Spiel zu starten
    if (pPlayer->GetObjectGuid() == pSpiel->GetLeiterGuid())
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SPIEL_STARTEN_LEITER, SENDER_SPIELER_LISTE, AKTION_SPIEL_STARTEN);
    }
    // Ein GM ist auch in der Lage das Spiel zu starten
    else if (pPlayer->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SPIEL_STARTEN_GM, SENDER_SPIELER_LISTE, AKTION_SPIEL_STARTEN);
    }

    char cAnzeige[100];
    char cAnzeige2[100];
    char cAnzeige3[100];
    char cAnzeige4[100];

    // Leben- & Killeranzahl, Status Killen- & Fluchtende aendern
    if (pPlayer->GetObjectGuid() == pSpiel->GetLeiterGuid())
    {
        sprintf(cAnzeige, pSpiel->GetNachricht(GOSSIP_LEBEN_MOD_LEITER), pSpiel->GetLebenAnzahl());
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige, SENDER_SPIELER_LISTE, AKTION_LEBEN_AUSWAHL);
        sprintf(cAnzeige2, pSpiel->GetNachricht(GOSSIP_KILLER_MOD_LEITER), pSpiel->GetKillerAnzahl());
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige2, SENDER_SPIELER_LISTE, AKTION_KILLER_AUSWAHL);
        sprintf(cAnzeige3, pSpiel->GetNachricht(GOSSIP_STATUS_KILLEN_ENDE_MOD_LEITER), uint32(pSpiel->GetStatusKillenEnde() / 60));
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige3, SENDER_SPIELER_LISTE, AKTION_KILLEN_ENDE_AUSWAHL);
        sprintf(cAnzeige4, pSpiel->GetNachricht(GOSSIP_STATUS_FLUCHT_ENDE_MOD_LEITER), uint32(pSpiel->GetStatusFluchtEnde() / 60));
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige4, SENDER_SPIELER_LISTE, AKTION_FLUCHT_ENDE_AUSWAHL);
    }
    // [GM] Leben- & Killeranzahl, Status Killen- & Fluchtende aendern
    else if (pPlayer->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
    {
        sprintf(cAnzeige, pSpiel->GetNachricht(GOSSIP_LEBEN_MOD_GM), pSpiel->GetLebenAnzahl());
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige, SENDER_SPIELER_LISTE, AKTION_LEBEN_AUSWAHL);
        sprintf(cAnzeige2, pSpiel->GetNachricht(GOSSIP_KILLER_MOD_GM), pSpiel->GetKillerAnzahl());
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige2, SENDER_SPIELER_LISTE, AKTION_KILLER_AUSWAHL);
        sprintf(cAnzeige3, pSpiel->GetNachricht(GOSSIP_STATUS_KILLEN_ENDE_MOD_GM), uint32(pSpiel->GetStatusKillenEnde() / 60));
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige3, SENDER_SPIELER_LISTE, AKTION_KILLEN_ENDE_AUSWAHL);
        sprintf(cAnzeige4, pSpiel->GetNachricht(GOSSIP_STATUS_FLUCHT_ENDE_MOD_GM), uint32(pSpiel->GetStatusFluchtEnde() / 60));
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige4, SENDER_SPIELER_LISTE, AKTION_FLUCHT_ENDE_AUSWAHL);
    }
    // Leben- & Killeranzahl, Status Killen- & Fluchtende anzeigen (Normal)
    else
    {
        sprintf(cAnzeige, pSpiel->GetNachricht(GOSSIP_LEBEN_NORMAL), pSpiel->GetLebenAnzahl());
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige, SENDER_SPIELER_LISTE, AKTION_SCHLIESSEN);
        sprintf(cAnzeige2, pSpiel->GetNachricht(GOSSIP_KILLER_NORMAL), pSpiel->GetKillerAnzahl());
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige2, SENDER_SPIELER_LISTE, AKTION_SCHLIESSEN);
        sprintf(cAnzeige3, pSpiel->GetNachricht(GOSSIP_STATUS_KILLEN_ENDE_NORMAL), uint32(pSpiel->GetStatusKillenEnde() / 60));
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige3, SENDER_SPIELER_LISTE, AKTION_SCHLIESSEN);
        sprintf(cAnzeige4, pSpiel->GetNachricht(GOSSIP_STATUS_FLUCHT_ENDE_NORMAL), uint32(pSpiel->GetStatusFluchtEnde() / 60));
        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige4, SENDER_SPIELER_LISTE, AKTION_SCHLIESSEN);
    }

    // Die Spielerliste wird erstellt
    pSpiel->ErstelleSpielerListe(pPlayer, 0, SENDER_SPIELER_LISTE2);

    // Aktualisieren
    pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_AKTUALISIEREN, SENDER_SPIELER_LISTE, AKTION_AKTUALISIEREN);

    // Spiel Entfernen
    if (pPlayer->GetObjectGuid() == pSpiel->GetLeiterGuid())
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SPIEL_ENTFERNEN_LEITER, SENDER_SPIELER_LISTE, AKTION_SPIEL_ENTFERNEN);
    }
    // Spiel Verlassen
    // [GM] Spiel Entfernen
    else if (pPlayer->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SPIEL_VERLASSEN, SENDER_SPIELER_LISTE, AKTION_SPIEL_VERLASSEN);
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SPIEL_ENTFERNEN_GM, SENDER_SPIELER_LISTE, AKTION_SPIEL_ENTFERNEN);
    }
    // Spiel Verlassen
    else
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SPIEL_VERLASSEN, SENDER_SPIELER_LISTE, AKTION_SPIEL_VERLASSEN);

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_BEIGETRETEN, pCreature->GetObjectGuid());
}

bool GossipHelloMrWho(Player* pPlayer, Creature* pCreature)
{
    // Der Spieler ist schon angemeldet
    if (WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid()))
    {
        SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
    }
    // Der Spieler ist noch nicht angemeldet
    else
    {
        pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, GOSSIP_SPIEL_ERSTELLEN, SENDER_MAIN, AKTION_SPIEL_ERSTELLEN, GOSSIP_SPIEL_NAME_EINGEBEN, 0, true);
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SPIEL_BEITRETEN, SENDER_MAIN, AKTION_SPIEL_BEITRETEN);
        pPlayer->ADD_GOSSIP_ITEM_ID(0, GOSSIP_SCHLIESSEN, SENDER_MAIN, AKTION_SCHLIESSEN);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_START_HALLO, pCreature->GetObjectGuid());
    }

    return true;
}

bool GossipSelectMrWho(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAktion) 
{
    switch (uiSender)
    {
        // uiAktion ist die Aktion
        case SENDER_MAIN:
        {
            switch (uiAktion)
            {
                case AKTION_SCHLIESSEN:
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case AKTION_SPIEL_BEITRETEN:
                    SpieleListeAnzeigen(pPlayer, pCreature);
                    break;
            }

            break;
        }
        case SENDER_SPIELE_LISTE:
            if (uiAktion == AKTION_AKTUALISIEREN)
            {
                SpieleListeAnzeigen(pPlayer, pCreature);
            }
            break;
        // uiAktion ist die SpielId
        case SENDER_SPIELE_LISTE2:
        {
            WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(uiAktion);

            // Wenn das Spiel nicht (mehr) existiert
            if (!pSpiel)
            {
                DoScriptText(TEXT_SPIEL_EXISTIERT_NICHT_MEHR, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Das Spiel kann nicht verlassen werden
            // weil es bereits gestartet wurde
            if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
            {
                DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Das Spiel ist bereits voll
            if (pSpiel->GetSpielerAnzahl() >= sWhoIsTheKillerMgrSD2::GetEinstellung(MAX_SPIELER_ANZAHL))
            {
                DoScriptText(TEXT_SPIEL_VOLL, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Anmeldungs Sound
            pPlayer->PlayDirectSound(SOUND_ANMELDEN, pPlayer);

            // Der Spieler wird angemeldet
            pSpiel->SpielBeitreten(pPlayer->GetObjectGuid());

            // Die Spielerliste wird angezeigt
            SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
            break;
        }
        case SENDER_SPIELER_LISTE:
        {
            // Hier brauchen wir gar keine SpielId :)
            if (uiAktion == AKTION_SCHLIESSEN)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }
            
            WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());

            // Wenn der Spieler nicht angemeldet ist
            if (!pSpiel)
            {
                DoScriptText(TEXT_NICHT_MEHR_ANGEMELDET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            switch (uiAktion)
            {
                case AKTION_SPIEL_STARTEN:
                    // Das Fenster wird geschlossen
                    pPlayer->CLOSE_GOSSIP_MENU();

                    // Nur Leiter und GMs duerfen das Spiel starten
                    if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
                    {
                        DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                        return true;
                    }

                    // Das Spiel wurde bereits gestartet
                    if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                    {
                        DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                        return true;
                    }

                    // Figuren konnten nicht verteilt
                    // werden (Zu wenige Spieler)
                    if (!pSpiel->SpielStarten())
                    {
                        DoScriptText(TEXT_ZU_WENIGE_SPIELER, pCreature, pPlayer);
                        return true;
                    }
                    break;
                case AKTION_LEBEN_AUSWAHL:
                {
                    // Nur Leiter und GMs duerfen die Leben von einem Spiel veraendern
                    if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
                    {
                        DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    // Das Spiel wurde bereits gestartet
                    if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                    {
                        DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    char cAnzeige[100];

                    for (uint8 ui = 0; ui < sWhoIsTheKillerMgrSD2::GetEinstellung(MAX_ANZAHL_LEBEN); ui++)
                    {
                        sprintf(cAnzeige, pSpiel->GetNachricht(GOSSIP_LEBEN_AUSWAHL), ui + 1);
                        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige, SENDER_LEBEN, ui + 1);
                    }

                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_ANZAHL_LEBEN, pCreature->GetObjectGuid());
                    break;
                }
                case AKTION_AKTUALISIEREN:
                    SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
                    break;
                case AKTION_SPIEL_ENTFERNEN:
                    // Das Fenster wird geschlossen
                    pPlayer->CLOSE_GOSSIP_MENU();

                    // Nur Leiter und GMs duerfen das Spiel entfernen
                    if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
                    {
                        DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                        return true;
                    }

                    // Das Spiel kann nicht verlassen werden
                    // weil es bereits gestartet wurde
                    if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                    {
                        DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                        return true;
                    }

                    // Abmeldungs Sound
                    pPlayer->PlayDirectSound(SOUND_ABMELDEN, pPlayer);

                    // Das Spiel wird entfernt
                    sWhoIsTheKillerMgrSD2::SpielEntfernen(pSpiel);
                    break;
                case AKTION_SPIEL_VERLASSEN:
                    // Das Fenster wird geschlossen
                    pPlayer->CLOSE_GOSSIP_MENU();

                    // Das Spiel kann nicht verlassen werden
                    // weil es bereits gestartet wurde
                    if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                    {
                        DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                        return true;
                    }

                    // Abmeldungs Sound
                    pPlayer->PlayDirectSound(SOUND_ABMELDEN, pPlayer);

                    // Ein Spieler will das Spiel verlassen
                    if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid())
                    {
                        pSpiel->SpielVerlassen(pPlayer->GetObjectGuid());
                    }
                    break;
                case AKTION_KILLER_AUSWAHL:
                {
                    // Nur Leiter und GMs duerfen die Killeranzahl von einem Spiel veraendern
                    if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
                    {
                        DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    // Das Spiel wurde bereits gestartet
                    if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                    {
                        DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    char cAnzeige[100];

                    for (uint8 ui = 0; ui < sWhoIsTheKillerMgrSD2::GetEinstellung(MAX_ANZAHL_KILLER); ui++)
                    {
                        sprintf(cAnzeige, pSpiel->GetNachricht(GOSSIP_KILLER_AUSWAHL), ui + 1);
                        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige, SENDER_KILLER, ui + 1);
                    }

                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_ANZAHL_KILLER, pCreature->GetObjectGuid());
                    break;
                }
                case AKTION_KILLEN_ENDE_AUSWAHL:
                {
                    // Nur Leiter und GMs duerfen die Zeit einstellen
                    if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
                    {
                        DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    // Das Spiel wurde bereits gestartet
                    if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                    {
                        DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    char cAnzeige[100];

                    for (uint8 ui = 0; ui < uint32(sizeof(aStatusKillenEndeAuswahl) / sizeof(uint32)); ui++)
                    {
                        sprintf(cAnzeige, pSpiel->GetNachricht(GOSSIP_STATUS_KILLEN_ENDE_AUSWAHL), uint32(aStatusKillenEndeAuswahl[ui] / 60));
                        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige, SENDER_KILLEN_ENDE, ui);
                    }

                    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
                    break;
                }
                case AKTION_FLUCHT_ENDE_AUSWAHL:
                {
                    // Nur Leiter und GMs duerfen die Zeit einstellen
                    if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
                    {
                        DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    // Das Spiel wurde bereits gestartet
                    if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                    {
                        DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                        pPlayer->CLOSE_GOSSIP_MENU();
                        return true;
                    }

                    char cAnzeige[100];

                    for (uint8 ui = 0; ui < uint32(sizeof(aStatusFluchtEndeAuswahl) / sizeof(uint32)); ui++)
                    {
                        sprintf(cAnzeige, pSpiel->GetNachricht(GOSSIP_STATUS_FLUCHT_ENDE_AUSWAHL), uint32(aStatusFluchtEndeAuswahl[ui] / 60));
                        pPlayer->ADD_GOSSIP_ITEM(0, cAnzeige, SENDER_FLUCHT_ENDE, ui);
                    }

                    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
                    break;
                }
            }
            break;
        }
        // uiAktion ist die uint32 Guid vom Spieler, der gekickt werden soll, oder 0 (Schliessen)
        case SENDER_SPIELER_LISTE2:
            if (uiAktion > 0)
            {
                WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());
                ObjectGuid KickGuid = ObjectGuid(HIGHGUID_PLAYER, 0, uiAktion);

                // Wenn der Spieler nicht angemeldet ist
                if (!pSpiel)
                {
                    DoScriptText(TEXT_NICHT_MEHR_ANGEMELDET, pCreature, pPlayer);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    return true;
                }

                // Das Spiel wurde bereits gestartet
                if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
                {
                    DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    return true;
                }

                // Nur Leiter und GMs duerfen Spieler kicken
                if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
                {
                    DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    return true;
                }

                // Das Fenster vom Gekickten wird geschlossen
                if (Player* pKick = pSpiel->GetSpieler(KickGuid))
                    pKick->CLOSE_GOSSIP_MENU();

                // Der Spieler wird aus dem Spiel gekickt
                pSpiel->SpielVerlassen(KickGuid);
                
                // Die Spieler-Liste wird aktualisiert
                SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
            }
            else
                pPlayer->CLOSE_GOSSIP_MENU();

            break;
        // uiAktion ist die Anzahl der Leben
        case SENDER_LEBEN:
        {
            WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());

            // Wenn der Spieler nicht angemeldet ist
            if (!pSpiel)
            {
                DoScriptText(TEXT_NICHT_MEHR_ANGEMELDET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Nur Leiter und GMs duerfen die Leben von einem Spiel veraendern
            if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
            {
                DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Das Spiel wurde bereits gestartet
            if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
            {
                DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Leben werden gesetzt
            pSpiel->SetLebenAnzahl(uiAktion);

            // Spielerliste wird angezeigt
            SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
            break;
        }
        // uiAktion ist die Anzahl der Killer
        case SENDER_KILLER:
        {
            WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());

            // Wenn der Spieler nicht angemeldet ist
            if (!pSpiel)
            {
                DoScriptText(TEXT_NICHT_MEHR_ANGEMELDET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Nur Leiter und GMs duerfen die Killeranzahl von einem Spiel veraendern
            if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
            {
                DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Das Spiel wurde bereits gestartet
            if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
            {
                DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Killer werden gesetzt
            pSpiel->SetKillerAnzahl(uiAktion);

            // Spielerliste wird angezeigt
            SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
            break;
        }
        // uiAktion ist der Index vom Auswahlarray
        case SENDER_KILLEN_ENDE:
        {
            WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());

            // Wenn der Spieler nicht angemeldet ist
            if (!pSpiel)
            {
                DoScriptText(TEXT_NICHT_MEHR_ANGEMELDET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Nur Leiter und GMs duerfen die Zeit veraendern
            if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
            {
                DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Das Spiel wurde bereits gestartet
            if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
            {
                DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Zeit wird gesetzt
            pSpiel->SetStatusKillenEnde(aStatusKillenEndeAuswahl[uiAktion]);

            // Spielerliste wird angezeigt
            SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
            break;
        }
        // uiAktion ist der Index vom Auswahlarray
        case SENDER_FLUCHT_ENDE:
        {
            WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());

            // Wenn der Spieler nicht angemeldet ist
            if (!pSpiel)
            {
                DoScriptText(TEXT_NICHT_MEHR_ANGEMELDET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Nur Leiter und GMs duerfen die Zeit veraendern
            if (pPlayer->GetObjectGuid() != pSpiel->GetLeiterGuid() && pPlayer->GetSession()->GetSecurity() < SEC_GAMEMASTER)
            {
                DoScriptText(TEXT_KEINE_RECHTE, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Das Spiel wurde bereits gestartet
            if (pSpiel->GetSpielStatus() != STATUS_WARTEN)
            {
                DoScriptText(TEXT_SPIEL_SCHON_GESTARTET, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return true;
            }

            // Zeit wird gesetzt
            pSpiel->SetStatusFluchtEnde(aStatusFluchtEndeAuswahl[uiAktion]);

            // Spielerliste wird angezeigt
            SpielerListeAnzeigen(pPlayer, pCreature, pSpiel);
            break;
        }
    }

    return true;
}

bool GossipSelectWithCodeMrWho(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAktion, const char* cCode)
{
    if (uiSender == SENDER_MAIN && uiAktion == AKTION_SPIEL_ERSTELLEN)
    {
        // Wenn der Name des Spiels eine bestimmte Laenge hat
        if (strlen(cCode) > 0 && strlen(cCode) <= sWhoIsTheKillerMgrSD2::GetEinstellung(MAX_ZEICHEN_SPIEL_NAME))
        {
            // Wenn nicht zuviele Spiele erstellt wurden
            if (sWhoIsTheKillerMgrSD2::GetSpieleAnzahl() < sWhoIsTheKillerMgrSD2::GetEinstellung(MAX_ERSTELLTE_SPIELE))
            {
                SpielerListeAnzeigen(pPlayer, pCreature, sWhoIsTheKillerMgrSD2::SpielErstellen(pPlayer->GetObjectGuid(), cCode));
            }
            // Zuviele Spiele wurden schon erstellt
            else
            {
                DoScriptText(TEXT_ZUVIELE_SPIELE, pCreature, pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
            }
        }
        // Name des Spiels ist zu lang
        else
        {
            DoScriptText(TEXT_SPIELNAME_ZU_LANG, pCreature, pPlayer);
            pPlayer->CLOSE_GOSSIP_MENU();
        }
    }

    return true;
}

bool GossipHelloMrWhoAbstimmen(Player* pPlayer, Creature* pCreature)
{
    WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());

    // Der Spieler spielt hier nicht mit
    if (!pSpiel)
    {
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_GRUSS_HALLO, pCreature->GetObjectGuid());
        return true;
    }

    // Wenn der Status nicht "STATUS_ABSTIMMEN" ist
    if (pSpiel->GetSpielStatus() != STATUS_ABSTIMMEN)
    {
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_GRUSS_HALLO, pCreature->GetObjectGuid());
        return true;
    }

    // Erstellt die Abstimmungsliste
    pSpiel->ErstelleAbstimmungsListe(pPlayer, 0, SENDER_ABSTIMMEN);
    
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_ABSTIMMEN, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelectMrWhoAbstimmen(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAktion) 
{
    if (uiSender == SENDER_ABSTIMMEN) 
    {
        WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());
        ObjectGuid TippGuid = ObjectGuid(HIGHGUID_PLAYER, 0, uiAktion);
        
        // Das Fenster wird geschlossen
        pPlayer->CLOSE_GOSSIP_MENU();

        // Der Spieler spielt hier nicht mit
        if (!pSpiel)
            return true;

        // Nur Camper koennen abstimmen
        if (pSpiel->IstAlsCamperAngemeldet(pPlayer->GetObjectGuid()))
        {
            pSpiel->Abstimmen(pPlayer->GetObjectGuid(), TippGuid);
            DoScriptText(TEXT_ABGESTIMMT_CAMPER, pCreature, pPlayer);
        }
        else if (pSpiel->IstAlsKillerAngemeldet(pPlayer->GetObjectGuid()))
            DoScriptText(TEXT_ABSTIMMEN_KILLER, pCreature, pPlayer);
    }

    return true;
}

bool GOUseFluchtPortal(Player* pPlayer, GameObject* pGo)
{
    WhoIsTheKillerSpiel* pSpiel = sWhoIsTheKillerMgrSD2::GetSpiel(pPlayer->GetObjectGuid());
        
    // Der Spieler spielt hier nicht mit
    if (!pSpiel)
        return true;

    // Der angemeldete Spieler ist nicht der Killer
    if (!pSpiel->IstAlsKillerAngemeldet(pPlayer->GetObjectGuid()))
        return true;

    // Wenn der Status nicht auf "STATUS_FLUCHT" ist
    if (pSpiel->GetSpielStatus() != STATUS_FLUCHT)
        return true;

    pSpiel->KillerPortal(pPlayer);
    return true;
}

void AddSC_who_is_the_killer()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name="MrWho";
    pNewScript->pGossipHello = &GossipHelloMrWho;
    pNewScript->pGossipSelect = &GossipSelectMrWho;
    pNewScript->pGossipSelectWithCode = &GossipSelectWithCodeMrWho;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="MrWhoAbstimmen";
    pNewScript->pGossipHello = &GossipHelloMrWhoAbstimmen;
    pNewScript->pGossipSelect = &GossipSelectMrWhoAbstimmen;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "FluchtPortal";
    pNewScript->pGOUse = &GOUseFluchtPortal;
    pNewScript->RegisterSelf();
}
