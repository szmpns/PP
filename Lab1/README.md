# [Szyfr Cezara / Caesar Cipher](./Szyfr_Cezara.c)

**PL:**  
Szyfr Cezara polega na szyfrowaniu kolejnych liter (pozostałe znaki pozostawiamy bez zmian). Każda litera zostaje zamieniona w k-tą następną w alfabecie (k jest stałą szyfru), przy czym jeżeli taka nie istnieje (wychodzimy za 'z'), to odliczanie jest kontynuowane z powrotem od 'a'. Szyfrowanie zachowuje wielkość liter. Napisz funkcję, która szyfruje ciąg znaków podany jako argument.

**ENG:**  
The Caesar Cipher involves encrypting individual letters while leaving other characters unchanged. Each letter is replaced by the k-th next one in the alphabet (where k is the cipher's constant), and if the shift moves past 'z', the counting continues from 'a'. The encryption preserves the case of the letters. Write a function that encrypts a string provided as an argument.