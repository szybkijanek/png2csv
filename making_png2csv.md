#Making png2csv

*Xcode* niestety nie ma dostępu do systemowego *libpng*.

	http://www.kyngchaos.com/software:frameworks
	
	The UnixImageIO framework. Common graphics format libraries in a 
	single framework. Image libraries included: GIF, JPEG, PNG, TIFF, 
	GeoTIFF, JasPer UUID.
	
Zaciągamy UnixImageIO. Nie można zainstalować paczki. Wymagany jest framework PROJ z tej samej strony. Teraz obie instalacje przebiegły pomyślnie.

Uruchamiamy *Xcode*. Tworzymy nowy projekt. Przenosimy do niego frameworki z */Library/Frameworks*. Koniecznie do listy, nie do właściwości.

Wrzućmy projekt na bitbucketa.

Magia konwersji:

	convert meteorogram.png PNG32:duupa.png 
	
Tworzymy RGB PNG z indeksowanego w ten sposób.