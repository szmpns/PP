# [Zgadnij liczbę / Guess the Number](./Zgadnij_liczbe.c)

**PL:**  
Program losuje liczbę \(0 \leq X < 100\). Napisz funkcję, która zgaduje wartość \(X\). W pętli losujemy \(n\) z przedziału \([0, 100)\). Jeżeli \(X = n\) zgadliśmy \(X\). Jeżeli nie, na podstawie wartości \(X\) i \(n\) ograniczamy przedział, z którego losujemy kolejne \(n\).

**ENG:**  
The program generates a random number \(0 \leq X < 100\). Write a function that guesses the value of \(X\). In a loop, we randomly select \(n\) from the range \([0, 100)\). If \(X = n\), we have guessed \(X\). If not, based on the values of \(X\) and \(n\), we narrow the range from which we draw the next \(n\).

# [Monte Carlo / Monte Carlo](./Monte_Carlo.c)

**PL:**  
Znajdź pole powierzchni ograniczone osią `0x` i wykresem funkcji `sin(x)` w przedziale `[a, b]` metodą Monte Carlo ([więcej informacji](https://pl.wikipedia.org/wiki/Metoda_Monte_Carlo)). Dane wejściowe: `a`, `b`, `N` (liczba losowanych punktów).

**ENG:**  
Find the area under the curve defined by the function `sin(x)` and the x-axis over the interval `[a, b]` using the Monte Carlo method ([more information](https://en.wikipedia.org/wiki/Monte_Carlo_method)). Input data: `a`, `b`, `N` (number of random points).

# [Szyfr Cezara / Caesar Cipher](./Szyfr_Cezara.c)

**PL:**  
Szyfr Cezara polega na szyfrowaniu kolejnych liter (pozostałe znaki pozostawiamy bez zmian). Każda litera zostaje zamieniona w k-tą następną w alfabecie (k jest stałą szyfru), przy czym jeżeli taka nie istnieje (wychodzimy za 'z'), to odliczanie jest kontynuowane z powrotem od 'a'. Szyfrowanie zachowuje wielkość liter. Napisz funkcję, która szyfruje ciąg znaków podany jako argument.

**ENG:**  
The Caesar Cipher involves encrypting individual letters while leaving other characters unchanged. Each letter is replaced by the k-th next one in the alphabet (where k is the cipher's constant), and if the shift moves past 'z', the counting continues from 'a'. The encryption preserves the case of the letters. Write a function that encrypts a string provided as an argument.