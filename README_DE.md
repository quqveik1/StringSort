# Textverarbeitungsprojekt

## Was das Hauptprojekt macht:
- Liest Text (in meinem Fall zum Beispiel der Text von Eugen Onegin)
- Teilt ihn in Zeilen auf
- Sortiert die Zeilen alphabetisch
- Sortiert die Zeilen von hinten (resultiert in Rap), da sich herausstellt, dass benachbarte Zeilen das gleiche Ende haben

## Besonderheiten des Projekts

- Verwendung von `string_view`, um die Programmausführung und die Geschwindigkeit der Textaufteilungsoperation zu beschleunigen. Im Gegensatz zu `std::string` bietet `string_view` eine unveränderliche Ansicht einer Zeichenfolge. Dies vermeidet unnötige Kopien und Speichernutzung bei der Zeichenfolgenverarbeitung, was den Code effizienter macht.
- Unterstützung für Unicode mit `std::wstring` und `std::wcout` für die korrekte Textverarbeitung in verschiedenen Sprachen und Plattformen.
- Unterstützt alle Plattformen, verwendet native `Win API`-Funktionen unter Windows.
- Eigene Sortierfunktion mit bekannter Asymptotik.

# `QuickSortUnitTest`

`QuickSortUnitTest` ist ein grafisches Teilprojekt zur Feinabstimmung der Koeffizienten Ihrer Schnell-Sortierfunktion mit Hilfe der Monte-Carlo-Methode und des Gradientenabstiegs. Die Sortierfunktion ist von der Form nlogn und wird mit der Funktion kx + b verglichen, implementiert auf der Basis der High-Level-Bibliothek [`TESTWIN32_GRAPHICAPP`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP).
Es wird zur Feinabstimmung der Koeffizienten der Sortierfunktion und zur Erstellung von Sortiereffizienzdiagrammen verwendet.

<img src="https://user-images.githubusercontent.com/64206443/235460597-0fbdd4c4-49d0-4fa8-a81e-cc3396697266.png" width="400">

--------------------------
# Anleitung zum Ausführen von `QuickSortUnitTest` unter Windows
- Voraussetzungen: Windows 7 ist für die vollständige Funktion des Programms erforderlich.
- Laden Sie die Anwendung von folgendem Link herunter: https://github.com/quqveik1/StringSort/releases/latest
- Führen Sie die heruntergeladene .exe-Datei aus, ignorieren Sie Antivirus-Warnungen, die besagen, dass das Programm gefährlich ist.
In diesem Fenster sollten Sie auf diese Schaltfläche klicken.

<img src="https://user-images.githubusercontent.com/64206443/182945554-ed4d18c6-a25d-4d0d-a331-e268643b3031.png" width="400">

- Der Programm-Installer wird geöffnet; folgen Sie seinen Anweisungen.
