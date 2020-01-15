# 🐺 WOLF QUEST 🐺

### 📝 Gameplay i info:
![readme](https://user-images.githubusercontent.com/43257971/72408798-38f41900-3764-11ea-864f-b0b488ca92fd.gif)<br>
Wolf Quest je tip endless runner igrice(skoro).Cilj je izbegavati prepreke krecuci se levo/desno i ne dozvoliti da te lavina zatrpa(zakaciti prepreku)."skoro endless" zato sto nisam mogao ostaviti da se tek tako igra do smrti vec su podeseni parametri za scor i kraj igre gde ako skupite preko 4800 poena(sto je zapravo 4800 puta pozvana funkcija za tajmer(run animation)) prozor se gasi i u terminalu stize poruka Co...(skupite ih 👍/ pronadjite u kodu 👎) ili ako pak zakacite prepreku i lavina Vas zatrpa u terminalu se ispise.. 😄
Traka sa preprekama je sacinjena od 3 dela(leva/mid/desna traka) i u zavinosti od pritiska dugmeta ◀ / ▶ Balto(vuk) se pomera u traku levo/desno od trenutne.<br>
:exclamation:Tip: Ne morate cekati da se Balto potpuno pomeri u u npr traku levo pa da onda krenete desno.

### :video_game: Komande:
<kbd>SPACE</kbd> - Pokretanje programa <br>
<kbd>ESC</kbd> - Izlazak iz programa

### :wrench: Instalacija i pokretanje programa:
Instalirati git:
* Linux terminal:`sudo apt install git`
* Ili sa sajta [https://www.atlassian.com/git/tutorials/install-git](https://www.atlassian.com/git/tutorials/install-git)

Instalirati OpenGL:
* Linux terminal(ulogovati se kao root korisnik):
  * Neophodni paketi `apt-get install freeglut3-dev`
  * OpenGl i GLUT man strane:
    * Preuzeti datoteku http://poincare.matf.bg.ac.rs/~ivan/files/rg/opengl_glut_manpages.tar.bz2
    * Izvrsiti sledece komande:
      * `cd /`
      * `tar xvjf /putanja/do/fajla/opengl_glut_manpages.tar.bz2`
* Ili sa sajta [https://www.prinmath.com/csci5229/misc/install.html](https://www.prinmath.com/csci5229/misc/install.html)

💬 Terminal:
* Klonirati projekat na racunar `git clone https://github.com/MATF-RG19/RG95-wolfquest.git`
* Pozicionirati se u direktorijum RG95-wolfquest `cd RG95-wolfquest`
* Pokrenuti Makefile `make` 🌲
* Pokrenuti igricu `./wolfQuest` 🐺
### Animirani film Balto(1995):
![ELAKMgkWoAA2mH6](https://user-images.githubusercontent.com/43257971/72405468-5374c500-3759-11ea-8618-d62efa43131c.jpg)

Godina 1925,Nome (Aljaska) je pogodjen virusom koji se jako brzo prosirio medju decom toga grada usled nedostatka antitoksina, zabacenosti grada od ostatka sveta i nezapamcene mecave, lek nije mogao biti dostavljen vozom/avionom. Jedina nada je bila psecja zaprega sacinjena od najboljih sibirskih haskija(organizovana je trka za izbor najspremnijih). 
7 haskija na celu sa Steelom (glavnim "zlikovcem") poslato je da donese antitoksin od Nenane do Noma. Na putu natrag mecava je prevladala i Steel,ostali psi i gonic su ostali izgubljeni u dubokom snegu.Nome je gubio nadu...<br>
Videvsi to, Balto je zajedno sa svojom druzinom ( Jenna Muk Luk i Boris) krenuo u spasilacku misiju. Na putu Jenna je povredjena i dok su je ostali bezbedno vracali kuci, Balto je potragu nastavio sam. Pre rastanka ide Boris(guska) sa prejakim savetom "Let me tell you something Balto. A dog can not make this journey alone, but maybe a wolf can."[https://www.youtube.com/watch?v=qKYld3RAXgQ](https://www.youtube.com/watch?v=qKYld3RAXgQ).<br>
Nakon pronalaska izgubljene zaprege Steel odbija da ga poluvuk vodi i cini sve kako Balto ne bi ispao heroj umesto njega, i u medjusobnoj borbi pada sa litice (kasnije zavarava trag kojim se Balto sluzio da se vrati kuci).
Balto postaje pas predvodnik i ostale pse sa povredjenim gononicem i lekom vraca kuci.Na putu ka Nomu jedna od prepreka je lavina, izazvana Starovim kijanjem ->[https://www.youtube.com/watch?v=Rmenugw8rwE&t=22s](https://www.youtube.com/watch?v=Rmenugw8rwE&t=22s).<br>
Ta scena sa lavinom je donekle preslikana u igrici a i njena slika je koriscena kao jedna tekstura, dok je druga i muzika iz scen...E pa kad ste dovde procitali pola sto prepricah, pogledajte vala ceo crtani ->[https://europixhd.io/mov/balto-1995-online-free-hd-with-subtitles-europix](https://europixhd.io/mov/balto-1995-online-free-hd-with-subtitles-europix). Mozda Vam posle toga bude jos lepse odigrati igricu.
### 📣 Napomena:
📦 biblioteka "irrKlangLib" za muziku preuzeta sa: [https://www.ambiera.com/irrklang/](https://www.ambiera.com/irrklang/)<br>
📦 biblioteka "imageLib" za teksture preuzeta od asistenta Rastka Djordjevica [http://www.matf.bg.ac.rs/p/-rastko-djordjevic](http://www.matf.bg.ac.rs/p/-rastko-djordjevic)
