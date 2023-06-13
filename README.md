# C-Algorithm-Optimization
A program made in C language to check how Unoptimized, Optimized and Basic Linear Algebra Subprograms matrix multiplication algorithms work and compare their execution time.

Nume: Neagu Robert - Andrei

NEOPT:
In programul solver_neopt.c am declarat 6 variabile, matrixATranspose pentru a stoca transpusa matricei superior triunghiulare A, matrixBTranspose pentru a stoca transpusa matricei B, partialLeftProduct pentru a stoca produsul partial B * A din termenul stang al ecuatiei, leftProduct in care am stocat produsul membrului stang al ecuatiei B * A * A transpus, rightProduct pentru a stoca produsul membrului drept B transpus * B al ecuatiei. In fiecare functie apelata se verifica daca alocarea rezultatului returnat a fost efectuata cu succes, se realizeaza operatia respectiva iar ulterior se returneaza rezultatul. La finalul programului se elibereaza memoria tuturor variabilelor folosite, mai putin cea a variabilei sum care se returneaza in functia my_solver.

OPT:
In programul solver_opt.c, asemenea ca in solver_neopt.c, am declarat 6 variabile enumerate anterior. In plus fata de neopt, la multiplicarea matricelor B * A, B * A * A transpus si B transpus * B, am folosit keyword-ul register pentru indecsii matricelor, iar in acest mod compilatorul poate avea grija ca variabilele respective sa fie tinute in registrii, permitand o utilizare optima a acestor resurse. De asemenea, am folosit pentru fiecare inmultire varianta optima cu pointeri, implementata in functiile multiplyBA, multiplyBAAtranspose si multiplyBBtranspose, varianta descrisa in laboratorul 5 din cadrul materiei, astfel reducand seminificativ timpii de rulare al algoritmului pe diferite numere de elemente.

BLAS:
In programul solver_blas.c am declarat 3 variabile, leftProduct, partialLeftProduct si rightProduct. Astfel, prin functia cblas_dcopy am copiat matricea B in matricea partialLeftProduct, pe care am inmultit-o ulterior cu matricea superior triunghiulara A cu ajutorul functiei cblas_dtrmm, rezultatul fiind scris in variabila partialLeftProduct. Ulterior am reapelat aceasta functie, realizand inmultirea dintre partialLeftProduct (in care avem B * A in acest punct) cu matricea A transpusa, care este inferior triunghiulara in acest caz, rezultatul fiind de asemenea scris in partialLeftProduct. Dupa aceea, am copiat rezultatul din partialLeftProduct in leftProduct, reprezentand rezultatul membrului stang al ecuatiei. Pentru membrul drept al ecuatiei am apelat functia cblas_dgemm care reprezinta inmultirea simpla a matricelor, iar cu ajutorul parametrului CblasTrans am specificat faptul ca primul termen de inmultit va trebui transpus. Astfel am inmultit B transpus cu B, iar rezultatul l-am scris in variabila rightProduct. In final, am apelat functia cblas_daxpy care aduna matricele leftProduct si rightProduct pentru a obtine ecuatia ceruta, ulterior am eliberat memoria din leftProduct si partialLeftProduct si am returnat variabila rightProduct care reprezinta rezultatul ecuatiei.


ANALIZA COMPARATIVA A PERFORMANTEI:

ELEMENTE: 200 NEOPT: 0.155769 OPT_M: 0.031623 BLAS: 0.005642
ELEMENTE: 400 NEOPT: 1.354642 OPT_M: 0.314716 BLAS: 0.032251
ELEMENTE: 600 NEOPT: 4.668956 OPT_M: 1.636038 BLAS: 0.101942
ELEMENTE: 800 NEOPT: 11.359429 OPT_M: 2.652237 BLAS: 0.221824
ELEMENTE: 1000 NEOPT: 20.623531 OPT_M: 4.51518 BLAS: 0.429972
ELEMENTE: 1200 NEOPT: 36.888802 OPT_M: 8.610617 BLAS: 0.716185
ELEMENTE: 1400 NEOPT: 62.166454 OPT_M: 14.39005 BLAS: 1.103358
ELEMENTE: 1600 NEOPT: 108.232964 OPT_M: 28.552423 BLAS: 1.664978

In setul de valori anterior se poate observa cum varianta optimizata manual, opt_m, este mult mai rapida, mai ales in cazul cu cel mai multe elemente (1600), timpul de rulare al algoritmului opt_m fiind de 3.85 ori mai scurt fata de cel neoptimizat, al inmultirii clasice al matricelor. Dintre toate 3 variantele, se poate observa foarte clar performanta deosebita a variantei BLAS, unde pentru 1600 de elemente, rularea algoritmului s-a produs doar in 1.66 secunde. Din analiza graficului se poate observa cum cresc timpii de rulare al algoritmilor neopt si opt_m in jurul valorilor de 1200, respectiv 1400 de elemente, probabil din posibila depasire a liniei cache-ului. In varianta neoptimizata, se poate observa cum timpul incepe sa creasca mult mai devreme, chiar de la aproximativ 1000 de elemente, in detrimentul algoritmului optimizat manual, unde timpul incepe sa creasca semnificativ in jurul valorii de 1400+ de elemente. Timpul variantei BLAS este tot foarte mic, in ciuda numarului mare de elemente, deoarece foloseste parcurgerea matricelor pe blocuri, astfel fiind folosit cache-ul foarte eficient.
