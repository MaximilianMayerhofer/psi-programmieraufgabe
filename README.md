# Programmieraufgabe

Die Aufgabe besteht in der Implementierung einer vereinfachten Form eines gerichteten azyklischen Graphen (englisch DAG, directed acyclic
graph).

**Bewertungskriterien**

- git und GitLab: Arbeiten Sie mit feature branches und schreiben Sie sinnvolle commits inkl. commit-Nachrichten. Bei
  Team-Arbeit: Erstellen Sie merge requests, um mit ihrem Partner den Code zu diskutieren.
- Achten Sie auf Code-Formatierung: Verwenden Sie eine einheitliche Code-Formatierung für das gesamte Projekt.
- Implementierung: Achten Sie auf Code und Design-Guidelines. Es geht nicht um die beste/effizienteste Implementierung.
  Der Code soll funktionieren und prinzipielle Grundregeln (z.B. DRY) beachtet werden.
- Tests: Erstellen Sie ausreichend viele und sinnvolle Tests für ihre Implementierung.

**Ablauf**

Die Aufgabe soll im Team bearbeitet werden. Falls nicht anders möglich ist auch eine Einzelbearbeitung möglich. Die
Bearbeitung ist in einem `Fork` des Projekts durchzuführen. Erstellen Sie zu jeder Teilaufgabe entsprechende commits
inklusive Dokumentation in `GitLab`.
**Erstellen Sie keine merge requests im ursprünglichen Repository. Arbeiten Sie ausschließlich in ihrem `Fork` des
Projekts. Achten Sie auf einen richtigen `target branch` beim Erstellen eines merge requests**

**Aufgabe**

Die vereinfachte Form des gerichteten azyklischen Graphen (englisch DAG, directed acyclic graph) soll folgende
Eigenschaften besitzen.

1. Der Graph besitzt genau einen Anfangsknoten (root node)
1. Ein Knoten kann beliebig viele Nachfolger-Knoten besitzen
1. Jedem Knoten ist eine Daten-Klasse zugeordnet. Eine einfache Data-Klasse finden Sie bereits vorgegeben
   in `src/data.h`. Dort sind auch zwei Hilfsfunktionen (`operator<<` und `operator==`) deklariert, die Sie
   implementieren sollen.
1. Einem Knoten kann die Methode `addNode(..)` in `src/node.h` ein Nachfolger-Knoten hinzugefügt werden.
1. Der Graph soll über die Methode `printGraph(...)` in `src/utility.h` in der Konsole dargestellt werden können. Wie
   ein entsprechender Test aussehen könnte, finden sie im Test `Print graph` in `tests/dag_tests.cpp`.
1. Die Methode `getRandomPath(..)` in `src/utility.h` soll einen zufälligen, gültigen Pfad zurück liefern. Dieser soll
   auch über `printGraph` ausgegeben werden.

Eine grobe Struktur ist bereits in diesem Projekt vorgegeben. Diese sollen Ihnen als Orientierung dienen. Sie können
alle Dateien beliebig verändern und auch neue Dateien erstellen.

Beachten Sie die Hinweise und Erläuterungen im entsprechenden Video auf moodle.

Zur Implementierung darf nur die C++-Standardbibliothek verwendet werden. Andere, externe Bibliotheken sind nicht
zulässig!

Überlegen Sie sich im Team die Implementierungsschritte (z.B. welche Klassen werden zuerst implementiert), die zur
Implementierung des DAG nötig sind. Achten Sie darauf dafür auch immer Tests zu schreiben! Der Implementierungsschritt
und die zugehörigen Tests sollen, wenn möglich, von unterschiedlichen Personen umgesetzt werden. Achten Sie auf eine
eindeutige Zuweisung der Schritte zu einer Person (diese soll aus der git-history ersichtlich sein). Sie müssen nicht
prüfen, ob der erstellte Graph azyklisch ist.
 
