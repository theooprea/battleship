Oprea Theodor-Alin 314 CC
Timp de implementare: 2 saptamani cu 1-5 ore in fiecare zi, in jur de 40 de ore

Utilizare:

IMPORTANT!
Pentru a utiliza feature-ul de muzica se apasa "m" in meniul principal, in
cazul in care e bifata optiunea de muzica modul de utilizare a muzicii este
urmatorul: o data ce incepe melodia fie se asculta pana la final, fie se muta
bara de play din jos-ul rhythmbox-ului pana la final pt a nu astepta toata
melodia si apoi se inchide rhythmboxul apasand x-ul din dreapta sus urmand ca
fereastra sa se schimbe automat (in cazul in care nu se inchide prematur
rhythmboxul programul nu are erori).
IMPORTANT!
Daca doriti sa vedeti versiunea mai stabila a jocului, cand nu se folosesc
melodiile in program si implicit nu mai sunt probleme la inchiderea
rhythmboxului prematur, se poate rula programul iar in meniul principal se lasa
optiunea de muzica pe OFF.
IMPORTANT!

Fie se ruleaza programul cu regula din Makefile cu comanda "make run" fie
se ruleaza executabilul ./battleship cu argumentele corespunzatoare, ofer 6
harti deja facute cu codarea '.' pentru gol/apa si 'X' pentru bucata de nava
in meniu sunt 3 alegeri, New Game, Resume Game si Quit. In cazul alegerii Quit
programul iese din joc, la Resume Game fie se afiseaza faptul ca nu s-a inceput
un nou joc fie se continua jocul din punctul in care a fost lasat jocul. La
selectarea unui noi joc intram in meniul de alegere al hartei jucatorului, de
unde putem vedea si alege hartile transmise ca parametrii executabilului. In
meniul principal se navigheaza folosind sageata sus si jos in timp ce in cel
pentru alegerea hartii jucatorului folosim sageata sus/jos sau r pentru a se
genera o harta random.

La intrarea in joc sunt afisate cele 2 harti/griduri, fiind specificat care
harta este a cui prin afisarea numelui sub acesta. De asemenea pe parcursul
jocului am afisat diferite mesaje ajutatoare, precum este randul jucatorului,
lovit/ratat, ai folosit abilitatea "X" si altele. Pentru a selecta o casuta
se folosesc sagetile iar pentru a confirma atacul se apasa enter. In cazul in
care jucatorul doreste sa atace random poate apasa tasta X, o abilitate care
mimeaza un atac al computerului. Pentru destroy in advance se apasa d iar in
mod similar pentru randomizare se apasa r. Daca jucatorul vrea sa iasa din joc
apasa tasta q, jocul putand fi reluat alegand Resume Game din main menu. Dupa
finalizarea unui joc este eliberat ecranul si se afiseaza rezultatul jocului,
player wins, computer wins, remiza si cate nave a doborat fiecare, jucatorul
si calculatorul. Jucatorul este indemnat sa apese o tasta pentru a trece mai
departe in program, unde se va afisa o imagine in conformitate cu rezultatul
jocului, o fata zambitoare daca a castigat jucatorul, o fata trista daca a
pierdut si un :P daca e remiza, toate imaginile desenate ca ASCII art.

Implementarea jocului:

Prima data am implementat meniul principal pentru care am folosit o functie
pentru a initializa modul curses si o fereastra, apoi am facut o functie
special pentru a afisa si a naviga in meniu. Afisez meniul si de fiecare data
cand schimb alegerea, de la New Game la Quit (trecand prin Resume Game) sau
alte posibilitati curat fereastra (clear()) apoi afisez iar aceleasi lucruri.
In funtie de alegerea facuta functia imi returneaza 0,1 sau 2. Cat timp
alegerea nu e 2 (nu s-a ales Quit) se alege fie joc nou fie continuarea unuia
deja ineput. Apoi am implementat functia de afisare a hartilor care prima data
afiseaza caracterele '-' si '|' la granitele hartilor iar inauntrul lor fie
'.' pentru apa sau 'X' pentru nava. Am folosit 3 matrice, una pentru jucator,
denumita player, una pentru computer, asemanatoare cu cea a jucatorului, numita
computer, si una pe care o afisez, e cea pe care o vede jucatorul in timpul
jocului, computer2. In timpul realizarii jocului am afisat si matricea computer
pt a ma verifica daca ce adaug in program e corect, lucru ce am dezactivat la
finalizarea programului.

Am creat dupa o functie de randomizare care primeste
ca parametrii si numarul de nave (fapt ce m-a ajutat apoi la realizarea
abilitatii de randomize in timpul jocului). Functie preia cate nave din fiecare
trebuie sa puna si folosesc un contor ok care initial e 1. Daca pe parcursul
generarii posibilitatilor de a pozitiona nava se incalca una dintre restrictii
contorul devine 0. La finalul generarii posibilitatii daca contorul este 1 va
pune nava, daca nu se reia procesul. Asta se face cu fiecare tip de nava, dupa
dimensiune. Apoi am implementat meniul de alegere a navei jucatorului, in modul
celui principal, se folosesc sageata sus/jos pt a alege fisierul din care se
incarca harta sau r pentru a se genera random harta. O data ce se ajunge la o
alegere se deschide fisierul si se afiseaza un preview al hartii in coltul din
stanga sus al ferestrei. In meniu sunt afisate si mesaje de ajutor pentru a
naviga prin meniu. O data decizia facuta se realizeaza matricea player. Am
realizat apoi functia "joaca" in care este implementat jocul propriu zis, sunt
in princiupiu 2 while-uri care reprezinta alegerile/atacurile playerului si al
computerului. Playerul are 5 alegeri, fie alege al casuta si ataca, fie ataca
random folosind tasta "x", fie alege din abilitati, destroy in advance apasand
"d" sau randomize apasand "r" sau iese din joc apasand tasta q pentru a se
intoare la meniul principal.

In functia joaca folosesc mai multi contori care tin de jocul in sine, precum
playerhit sau computerhit care permit continuarea jocului dupa ce un atac este
lovit, abilitate care imi arata daca am folosit o abilitate, quit daca am ales
sa ies din joc (sau daca s-a terminat jocul) dar si variabile de genul
lasthiti, lasthitj sau lasthithorvert prin care verific in primul rand daca
trebuie sa folosesc strategia de a lovi in jurul unui loc gasit si in ce
directii sa traga computerul apoi.

In final am implementat functiile abilitate, randomizemid game pt a randomiza
harta jucatorului, destroy in advance si randomshot, abilitate care mimeaza o
lovitura a computerului, la intamplare, in cazul in care jucatorul nu se decide
unde sa atace. Pentru randomize mid-game am folosit inca o functie de a detecta
cate nave de 4,3,2 sau 1 block mai sunt in viata, functie pe care o apelez si
in main pentru score-ul final. Pentru destroy in advance am facut inca o
functie auxiliara care ma ajuta sa vad daca mai sunt casute goale, numita
sugestiv "maisuntcasutelibere". Functia de randomshot nu a necesitat altele
auxiliare. Am implementat de asemenea o functie de afisare a unei imagini de
tip ASCII art, pe care am folosit-o pentru a afisa titlul jocului dar si
imaginile de la finalul lui. Pt initializarea unui meci am folosit inca 2
functii de alocare si initializare a matricilor, player si computer trebuiau
initializate cu '.' iar computer2 cu ' ' pentru a da impresia unei fog of war
la inceputul jocului. De asemenea am folosit inca o functie care verifica daca
un joc a fost terminat si care este rezultatul acestuia, aceasta cauta 'X' in
ambele matrice si returneaza 0 daca jocul nu s-a terminat, 1 daca jucatorul a
terminat, 2 daca a castigat computerul si 3 daca e remiza.

Bonusuri:

Am implementat posibilitatea jucatorului de a-si alege singur harta din
argumentele date in linie de comanda si de a le vedea in timp ce parcurge
argumentele. In plus, daca acestuia nu ii plac hartile predefinite are optiunea
de a utiliza o harta random creata.

Am adaugat o strategie de joc pentru calculator, in cazul in care acesta
loveste o nava. Commputerul va incepe sa caute in jur iar cand a determinat
orientarea navei lovite, orizontal sau vertical, folosind o variabila numita
lasthithorvert, va ataca doar pe acele directii, sus/jos sau stanga dreapta. La
finalul atacului, cand a doborat nava va face o lovitura random.

Am implementat posibilitatea jucatorului de a ataca la nimereala, in cazul in
care nu stie unde sa atace. Asta se poate face apasand tasta "x". La finalul
atacului, in functie de rezultat (playerhit se transmite cu pointer la functie)
este fie randul jucatorului fie al computerului, se pastreaza regula daca ai
lovit este tot randul tau.

Am adaugat cateva imagini de tip ASCII art in joc, titlul jocului si cateva
imagini la final de joc. Am facut asta deschizand cateva fisiere text din care
citesc linie cu linie si afisez ce gasesc.

Am introdus 4 melodii in functie de punctul in care ma aflu in program, am o
melodie cand castiga jucatorul, una cand pierde, una cand e remiza si una cand
se iese din program. Acest lucru e realizat folosind aplicatia implicita de
executat mp3 din Linux, Rhythmbox

Codarea hartilor:
'.' pentru apa
'X' pentru o bucata de nava
'D' pentru o bucata de nava distrusa (destroyed)
'M' pentru o portiune de apa incercata (missed)

O varianta de harta poate fi:
........X.
........X.
.XXX..X.X.
........X.
.X........
...XXX..X.
.X........
.......XX.
.XX.XX....
..........
unde '.' este apa si 'X' parte de nava
