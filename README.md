# 🐺 WOLF QUEST 

### 📝 Gameplay i info:
![readme](https://user-images.githubusercontent.com/43257971/72408798-38f41900-3764-11ea-864f-b0b488ca92fd.gif)<br>
Wolf Quest je tip endless runner igrice(skoro).Cilj je izbegavati prepreke krecuci se levo/desno i ne dozvoliti da te lavina zatrpa(zakaciti prepreku)."skoro endless" zato sto nisam mogao ostaviti da se tek tako igra do smrti vec su podeseni parametri za scor i kraj igre gde ako skupite preko 4800 poena(sto je zapravo 4800 puta pozvana funkcija za tajmer(run animation)) prozor se gasi i u terminalu stize poruka Co...(skupite ih 👍/ pronadjite u kodu 👎) ili ako pak zakacite prepreku i lavina Vas zatrpa u terminalu se ispise.. 😄
Traka sa preprekama je sacinjena od 3 dela i u zavinosti od pritiska dugmeta ◀ / ▶ Balto(vuk) se pomera u traku levo/desno od trenutne.<br>
:exclamation:Tip: Ne morate cekati da se animacija kretanja npr desno potpuno zavrsi kako bi skrenuli levo

| :video_game: Komande |📜 Opis |
| --- | --- |
| <kbd> SPACE </kdb> | start |
| <kbd> ESC </kbd> | izlaz |
| <kbd> LEFT ARROW </kbd> | skretanje levo |
| <kbd> RIGHT ARROW </kbd> | skretanje desno |

:exclamation: Potrebno je ponovo pokrenuti igricu ukoliko zelite dalje igrati, ne postoji reset dugme
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
![ELAKMgkWoAA2mH6](https://user-images.githubusercontent.com/43257971/72405468-5374c500-3759-11ea-8618-d62efa43131c.jpg)<br>
Inspiraciju projekta predstavlja crtani Balto, odakle su preuzeti likovi, scenografija i muzika. Igrica predstavlja ozivljavanje scene u kojoj glavni junak bezi od lavine->[https://www.youtube.com/watch?v=Rmenugw8rwE&t=22s](https://www.youtube.com/watch?v=Rmenugw8rwE&t=22s).<br>
Za kompletni dozivljaj preporucujem gledanje celokupnog crtanog filma ->[https://europixhd.io/mov/balto-1995-online-free-hd-with-subtitles-europix](https://europixhd.io/mov/balto-1995-online-free-hd-with-subtitles-europix). <br>
Nadam se da ce Vam se dopasti! 🐺
### 📣 Napomena:
📦 biblioteka "irrKlangLib" za muziku preuzeta sa: [https://www.ambiera.com/irrklang/](https://www.ambiera.com/irrklang/)<br>
📦 biblioteka "imageLib" za teksture preuzeta od asistenta Rastka Djordjevica [http://www.matf.bg.ac.rs/p/-rastko-djordjevic](http://www.matf.bg.ac.rs/p/-rastko-djordjevic)
