#Instalacja
Program napisany jest w C++11, więc czysty gcc sobie z nim nie poradzi. Wbudowaną obsługę C++11 ma LLVM.
Wymagane:

* clang
* libpng

Sama instalacja to proste:

	make; make install; make clean


#PNGtoCSV
Broń boże nie będzie to **OCR**. Analizowane pliki **PNG** zostały wcześniej wygenerowane na serwerze **ICM**u, prawdopodobnie przy użyciu **gnuplota** albo czegoś podobnego i w **nieskompresowanej** formie udostępnione do pobrania. Nie przybliżamy więc odczytu na bazie materiału optycznego, tylko dysponujemy **niezakłamanym** ciągiem bitów z **zakodowanymi** danymi, dostępnymi w nim z dokładnością wynikającą ze skali wykresów i rozdzielczości pliku **PNG**.

Dlaczego **ICM** ułatwiło nam sprawę? To proste. Optymalizacja czasu. Pojedynczy meteorogram generuje się kilka sekund. To naprawdę długo. Dodanie antyaliasingu do znaków i kompresja pliku wynikowego byłyby dodatkowym, uciążliwym dla serwera narzutem. Uruchomili poza tym cache i nie generują codziennie diagramów dla wszystkich możliwych punktów, ograniczając się do generowania ich na bieżąco na żądanie użytkownika.

W dodatku, dokładność danych na diagramach była znacznie większa niż wymagana przez nas do projektu.

Nie dokonujemy więc żadnej magii, tylko tworzymy **dekoder**, składający się z kilku modułów:

* analizator wstępny (z nazwy pliku):
	* pozycja (generowanie station_id),
	* data,
	* powiązanie kolumny z timestampem,
* klasy traktującej plik png jak dwuwymiarową tablicę,
* kodera wzorca znaków:
	* generowanie wzorca znaków z pliku png,
	* generowanie tabeli wzorców, 
* *poszukiwacza* łańcuchów z zadanej tabeli wzorców na zakreślonym podobszarze tablicy (łańcuch składa się ze wszystkich znaków obecnych w jednej linii podobszaru, pozwala również na poszukiwanie tylko pierwszej lub tylko ostatniej linii):
	* odszukanie wszystkich łańcuchów,
	* odszukanie pierwszego łańcucha,
	* odszukanie ostatniego łańcucha,
* klasy skali:
	* generowanie skali z pierwszego i ostatniego łańcucha razem z ich wysokościami (prosty model matematyczny),
	* podawanie wartości dla wiersza,
* *poszukiwacza* odczytu (pierwszy kontakt danego zakresu danej kolumny z linią odczytu na diagramie)
* generatora CSV (na bazie kilku odczytów z kilku diagramów w pliku PNG, sparowanych z ich skalami)

Dekoder posiadać będzie własny prosty metajęzyk:
	
* **pattogen *znak.png*** - utworzenie wzorca dla znaku z zadanego pliku,
* **pattotab *nazwatablicy.pattab* *znak1.pat* [*znak2.pat* *znak3.pat* …]** - tworzenie tablicy ze wzorców,
* **pattoload *nazwatablicy.pattab*** - wczytanie tablicy wzorców,
* **setdiag *x:y:width:height:dev* *color:width*** - deklaracja obszaru poszukiwań (deklaracja lokalizacji skali (wraz z odchyleniem od obszaru diagramu), i parametrów linii),
* **output *nazwapliku.csv*** - deklaracja pliku csv,
* **analize *nazwapliku.png*** - przetwarzanie pliku z meteorogramami.

Przed rozpoczęciem pracy, jednorazowo dla formatu pliku z meteorogramami tworzymy z wyodrębnionych wcześniej plików png ze znakami pliki wzorców (**pattogen**), i łączymy je w tabelę (**pattotab**).

Rozpoczynając pracę wczytujemy tablicę ze wzorcami (**pattoload**) i deklarujemy obszary poszukiwań (**setdiag**) oraz nazwę pliku wynikowego (**output**). Następnie, kolejno, analizujemy pliki z meteorogramami (**analize**).

Wszystko programujemy w **C++** z wykorzystaniem **libpng**.

##Wzorce znaków
Na szczęście nikt nie zastosował antyaliasingu, więc możemy wykorzystać prostą w implementacji, autorską (choć pewnie ktoś wcześniej na to wpadł, nie rozglądałem się za tym przesadnie) metodę.
###Format wzorca
####Kod znaku
####Wymiar
####Ciąg bitów - zmiana *koloru*
###Implementacja konwertera znaku w PNG na format wzorca
###Tablica wzorców