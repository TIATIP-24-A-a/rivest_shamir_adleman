# Projektdokumentation: RSA-Algorithmus in C++

## Einleitung

Für unser Projekt haben wir uns entschieden, den RSA-Verschlüsselungsalgorithmus in **C++** zu implementieren, um neue Erkenntnisse über Kryptographie und die Entwicklung komplexer Algorithmen zu gewinnen. Bereits zu Beginn haben wir uns darauf geeinigt, nach den Richtlinien des **Google C++ Style Guides** zu arbeiten, um eine einheitliche und gut dokumentierte Codebasis zu gewährleisten.

**Quelle für den Style Guide:**  
[Google C++ Style Guide](https://sun.iwu.edu/~mliffito/cs_codex/posts/google-c++-style-guide/)

---

## Recherche

### Grundlagen des RSA-Algorithmus
Um eine solide Basis für die Implementierung zu schaffen, haben wir uns zunächst mit den Grundlagen des RSA-Algorithmus vertraut gemacht:
- Wie funktioniert die Schlüsselerzeugung (Public Key, Private Key)?
- Wie können Nachrichten mit Hilfe von Modulararithmetik und Primzahlen verschlüsselt und entschlüsselt werden?

Hierbei war der Artikel von Splunk besonders hilfreich, der die Funktionsweise des RSA-Algorithmus verständlich erläutert.

**Quelle:**  
[RSA Algorithm in Cryptography – Splunk](https://www.splunk.com/en_us/blog/learn/rsa-algorithm-cryptography.html)

### Von Integer- zur Textverschlüsselung
Zunächst implementierten wir eine einfache RSA-Verschlüsselung für Ganzzahlen, basierend auf den Erkenntnissen aus der Recherche. Doch schnell wurde klar, dass die reine Verschlüsselung von Zahlen nicht ausreicht, um die Funktionalität des Algorithmus umfassend zu verstehen. Daher entschieden wir uns, den Algorithmus zu erweitern, sodass er auch Texte verarbeiten kann. Dies erforderte zusätzliche Recherche und die Entwicklung eines benutzerdefinierten Datentyps.

### Entwicklung eines benutzerdefinierten Datentyps: BigNumber
Da Standarddatentypen wie `int` oder `long` für RSA mit grossen Zahlen nicht ausreichen, haben wir einen benutzerdefinierten Datentyp namens `BigNumber` entwickelt. Dieser ermöglicht die Verarbeitung beliebig grosser Zahlen und beinhaltet die Implementierung grundlegender Operatoren wie `+`, `-`, `*`, `/` und `%`. Besonders hilfreich war hierbei ein Artikel über die Erstellung von benutzerdefinierten Zuweisungsoperatoren in C++.

**Quelle:**  
[How to Create Custom Assignment Operator in C++ – GeeksforGeeks](https://www.geeksforgeeks.org/how-to-create-custom-assignment-operator-in-cpp/)

---

## Umsetzung

### Schritte der Implementierung

1. **Grundlagenimplementierung**:  
   Basierend auf der Splunk-Dokumentation wurde eine einfache RSA-Implementierung für Ganzzahlen erstellt.

2. **Entwicklung von BigNumber**:  
   Ein benutzerdefinierter Datentyp wurde entwickelt, um grössere Werte zu unterstützen, einschliesslich der Implementierung und Optimierung von Operatoren wie `+`, `-`, `*`, `/` und `%`.

3. **Erweiterung auf Textverschlüsselung**:  
   Der Algorithmus wurde so erweitert, dass Texte in numerische Werte codiert und anschliessend verschlüsselt und entschlüsselt werden können.

Am Schluss griffen wir jedoch auf **OpenSSL Best Practices** zurück, da unser eigener BigNumber-Datentyp nicht effizient genug war. Dies wird in den Erkenntnissen weiter erläutert, wo wir unsere Erfahrungen und Lernergebnisse festgehalten haben. Trotz der Herausforderungen haben wir in diesem Projekt viel gelernt.


---

## Herausforderungen

- **Komplexität von BigNumber**:  
  Die Implementierung eigener Operatoren wie `%` und `/` war herausfordernd. Fehler in diesen Operatoren führten oft zu unerwartetem Verhalten und verlangten gründliches Debugging.

- **Effizienzprobleme**:  
  Ohne Optimierungen war die Verarbeitung grosser Zahlen zeitaufwendig. Dies führte dazu, dass wir Teile des Codes auf Effizienz überprüften und anpassten.

- **Kryptographische Logik**:  
  Die korrekte Wahl von Public und Private Keys sowie deren Validierung erwies sich als anspruchsvoll.

---

## Erkenntnisse

### Technische Erkenntnisse
1. **BigNumber-Implementierung**:  
   Die Erstellung eines eigenen Ganzzahl-Datentyps hat gezeigt, wie schnell selbst grundlegende Operationen wie Addition oder Multiplikation komplex werden können. Für zukünftige Projekte könnten bestehende Bibliotheken wie GMP oder Boost sinnvoller sein, um Effizienz und Genauigkeit zu gewährleisten.

2. **RSA-Logik**:  
   Wir haben ein tiefes Verständnis für die kryptographischen Grundlagen des RSA-Algorithmus gewonnen. Insbesondere wurde deutlich, wie wichtig es ist, Public und Private Keys korrekt zu generieren, um Verschlüsselung und Entschlüsselung zuverlässig zu gewährleisten.

### Teamarbeit
Die Arbeit im Team brachte weitere wertvolle Erkenntnisse:
- **Kommunikation**: Regelmässige Absprachen waren entscheidend, um sicherzustellen, dass beide Mitglieder denselben Wissensstand haben.
- **Iterativer Ansatz**: Schrittweise Entwicklung und regelmässige Code-Reviews trugen wesentlich zur Qualität des Projekts bei.

---

## Fazit

Das Projekt war ein voller Erfolg. Wir konnten den RSA-Algorithmus vollständig implementieren und auf Textverschlüsselung erweitern. Gleichzeitig haben wir wertvolle Einblicke in die Entwicklung benutzerdefinierter Datentypen und die Zusammenarbeit im Team gewonnen.

Die gewonnenen Erkenntnisse – insbesondere über die Herausforderungen und Komplexität der BigNumber-Implementierung sowie die Kryptographielogik – werden uns bei zukünftigen Projekten von grossem Nutzen sein.
