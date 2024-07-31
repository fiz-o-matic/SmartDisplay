Offene Punkte für EA-Programm
- Ausrichtng LCD anpassen
    -> sollte soweit passen
- Anpassung Spannungsteiler für 5V MCU -> erledigt



Prüfung im EA-Programm
- Trip prüfen -> erledigt
- Test Hintergrundbeleuchtung -> OK -> Widerstände OK?

- Dokumentation anfangen
    - angefangen...

Punkte nach EA-Programm
- Frame für OLED SH1106 -> gestrichen
- Power Saving -> aktuell unter 20mA
- Anpassung OLED Display für Values Anzeige? ->gestrichen


Beta Programm fertig machen
-> erledigt


Fehlende Funktionen
- Trip Reset -> erledigt
- Trip im EEPROM speichern



TinyGPS / CAN
- verursacht einen Delay
- bei zu schnellen Lesen gehen Daten verloren
- keine freien Interrupts wenn alles zu schnell hintereinander läuft...


Contrast
- u8g2.setContrast(20)

Anzeige für Values bei mehr als 5 Stellen
- verschieben vom Suffix etwas nach oben so das es keine Überschneidung gibt.