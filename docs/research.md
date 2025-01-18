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

---

## Funktionsweise und unser Vorgehen

### Organisation und Teamarbeit
Um die Implementierung effizient zu gestalten, haben wir ein **Jira-Board** genutzt, auf dem wir alle Aufgaben als Tickets strukturiert haben. Jedes Teammitglied hat sich aktiv Tickets ausgesucht und daran gearbeitet. Durch regelmässige Abstimmungen und einen stetigen Austausch im Team konnten wir sicherstellen, dass jeder auf dem gleichen Stand war und Probleme zeitnah gelöst wurden.

---

### Eigenentwicklung von Grund auf
Wir haben zunächst versucht, den RSA-Algorithmus vollständig von Grund auf selbst zu implementieren. Dies umfasste auch die Entwicklung eines eigenen Datentyps namens `BigNumber`, um mit den sehr grossen Zahlen zu arbeiten, die bei RSA benötigt werden. Dieser Datentyp unterstützte grundlegende Operatoren wie `+`, `-`, `*`, `/` und `%`. Obwohl diese Implementierung funktionierte, war sie extrem ineffizient. Selbst bei einer RSA-Verschlüsselung mit nur 512 Bits dauerte die Berechnung mehrere Minuten.

### Recherche nach Best Practices
Da unsere eigene Implementierung ineffizient war, haben wir intensiv im Internet recherchiert, um Best Practices für RSA-Implementierungen in C++ zu finden. Während dieser Recherche sind wir auf eine hilfreiche Antwort auf **Stack Overflow** gestossen, in der OpenSSL als empfohlene Bibliothek erwähnt wurde. OpenSSL bietet eine effiziente und kostenlose Möglichkeit, RSA zu implementieren.

**Quelle für die Empfehlung:**  
[RSA Encryption Library for C++ – Stack Overflow](https://stackoverflow.com/questions/108518/rsa-encryption-library-for-c)

### Wechsel zu OpenSSL
Basierend auf dieser Empfehlung entschieden wir uns, OpenSSL in unserem Projekt zu verwenden. Konkret nutzten wir die Bibliothek **BIGNUM** von OpenSSL, die speziell für solche Berechnungen optimiert ist. Wir entwickelten einen eigenen Wrapper für BIGNUM, um die Nutzung in unserem Code zu vereinfachen und die Modularität zu erhalten. Dies ermöglichte eine deutlich schnellere und robustere Umsetzung des RSA-Algorithmus.

**Quelle für BIGNUM:**  
[OpenSSL BIGNUM Documentation](https://docs.openssl.org/1.0.2/man3/bn/)

---

## Umsetzung

### Schritte der Implementierung

1. **Grundlagenimplementierung**:  
   Basierend auf der Splunk-Dokumentation wurde eine einfache RSA-Implementierung für Ganzzahlen erstellt.

2. **Entwicklung von BigNumber**:  
   Ein benutzerdefinierter Datentyp wurde entwickelt, um grössere Werte zu unterstützen, einschliesslich der Implementierung und Optimierung von Operatoren wie `+`, `-`, `*`, `/` und `%`.

3. **Recherche und Wechsel zu OpenSSL**:  
   Nach intensiver Recherche haben wir uns für OpenSSL entschieden, da unsere eigene BigNumber-Klasse ineffizient war. Wir entwickelten einen Wrapper für die BIGNUM-Bibliothek, um auf optimierte Funktionen zurückzugreifen und die Performance erheblich zu steigern.

4. **Erweiterung auf Textverschlüsselung**:  
   Der Algorithmus wurde so erweitert, dass Texte in numerische Werte codiert und anschliessend verschlüsselt und entschlüsselt werden konnten.

---

## Herausforderungen

- **Komplexität von BigNumber**:  
  Die Implementierung eigener Operatoren wie `%` und `/` war herausfordernd. Fehler in diesen Operatoren führten oft zu unerwartetem Verhalten und verlangten gründliches Debugging.

- **Effizienzprobleme**:  
  Ohne Optimierungen war die Verarbeitung grosser Zahlen zeitaufwendig. Der Wechsel zu OpenSSL löste dieses Problem.

- **Kryptographische Logik**:  
  Die korrekte Wahl von Public und Private Keys sowie deren Validierung erwies sich als anspruchsvoll.

---

## Erkenntnisse

### Technische Erkenntnisse
1. **BigNumber-Implementierung**:  
   Die Eigenentwicklung eines Ganzzahl-Datentyps zeigte die Komplexität solcher Aufgaben auf. Bestehende Bibliotheken wie OpenSSL sind oft die bessere Wahl für Effizienz und Genauigkeit.

2. **OpenSSL-Wrapper**:  
   Durch die Erstellung eines Wrappers für BIGNUM konnten wir die Vorteile der OpenSSL-Bibliothek nutzen und gleichzeitig eine saubere, modulare Struktur beibehalten.

3. **RSA-Logik**:  
   Wir haben ein tiefes Verständnis für die kryptographischen Grundlagen des RSA-Algorithmus gewonnen. Insbesondere wurde deutlich, wie wichtig es ist, Public und Private Keys korrekt zu generieren.

### Teamarbeit
Die Arbeit im Team brachte weitere wertvolle Erkenntnisse:
- **Kommunikation**: Regelmässige Absprachen waren entscheidend, um sicherzustellen, dass beide Mitglieder denselben Wissensstand hatten.
- **Iterativer Ansatz**: Schrittweise Entwicklung und regelmässige Code-Reviews trugen wesentlich zur Qualität des Projekts bei.

---

## Fazit

Das Projekt war ein voller Erfolg. Wir konnten den RSA-Algorithmus vollständig implementieren und durch den Wechsel zu OpenSSL effizient umsetzen. Gleichzeitig haben wir wertvolle Einblicke in die Entwicklung benutzerdefinierter Datentypen und die Zusammenarbeit im Team gewonnen.

Die gewonnenen Erkenntnisse – insbesondere über die Herausforderungen der BigNumber-Implementierung und die Kryptographielogik – werden uns bei zukünftigen Projekten von grossem Nutzen sein.
