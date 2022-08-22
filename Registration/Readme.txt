Завдання:
Реалізувати валідацію наступних типів введених даних

username
Може містити лише літери латинського алфавіту та дефіси.
Може складатися з кількох слів.
Слово не може починатися з дефісу.

login
Може містити лише латинські літери, цифри, дефіси та підкреслення. Не може починатися з дефісу та підкреслення.

password
Не може містити літери, відмінні від латинських.
Не може містити прогалини, переклади рядка, табуляцію тощо.
Перевірка безпеки повинен містити великі та маленькі літери латинського алфавіту, цифри та спецсимволи. Відстежити, чого не вистачає для безпеки.

phone, domain, e-mail, credit card number, ip address
З'ясувати, як правильно валідувати кожне з цих полів у проф. Гугля.
Реалізувати валідацію.

domain
Доменне ім'я складається мінімум з двох і максимум з 63 символів.
Допускаються всі літери від a до z, усі цифри від 0 до 9 і дефіс (-).
Доменне ім’я не повинно складатися з дефіса (-) на третій і четвертій позиції одночасно.
Також можливі такі спеціальні символи. Доменні імена, що містять такі літери, називаються IDN або інтернаціоналізованими доменними іменами:
ß, à, Á, â, ã, ó, ô, þ, ü, ú, ð, æ, å, ï, ç, è, õ, ö, ÿ, ý, ò, ä, œ, ê, ë, ì, í, ø, ù, î, û, ñ, é

e-mail
Прийнятні формати префіксів електронної пошти
Дозволені символи: літери (az), цифри, підкреслення, крапки та тире + дивись domain (після @).
Після підкреслення, крапки або тире має йти одна або кілька літер або цифр.

credit card number
У техніці перевірки номерів кредитних карток використовується формула Луна (також відома як алгоритм Луна або алгоритм «mod 10» або «modulus 10»). Це проста процедура, яка перевіряє номер картки в три етапи:

Подвоїть значення кожної непарної цифри номера картки, яку ви перевіряєте. Якщо отримана сума будь-якої операції подвоєння більша за 9 (наприклад, 6 x 2 = 12 або 8 x 2 = 16), тоді додайте цифри цієї суми (наприклад, 12: 1 + 2 = 3 або 16: 1 + 6 = 7).
Складіть усі отримані цифри, включаючи парні цифри, які ви не помножили на два.
Якщо сума, яку ви отримали, закінчується на 0, номер картки дійсний згідно з формулою Луна; інакше він недійсний.

Будьте уважні! Айпі адреса - це не просто чотири числа, а номер кредитки - не просто 16 цифр!

------------------------------------------------- ---------
файли out.txt і users.csv закинути в папку з програмою... або вказати шлях.


------------------------------------------------- ---------
Задача:

Реализовать валидацию следующих типов введённых данных

 username
Может содержать только буквы латинского алфавита и дефисы.
Может состоять из нескольких слов.
Слово не может начинаться с дефиса.

 login
Может содержать только латинские буквы, цифры, дефисы и подчёркивания. Не может начинаться с дефиса и подчёркивания.

 password
Не может содержать буквы, отличные от латинских.
Не может содержать пробелы, переводы строки, табуляцию и т.п.
Проверка безоспасности должен содержать большие и маленькие буквы латинского алфавита, цифры и спецсимволы. Отследить, чего не хватает для безопасности.

 phone, domain, e-mail, credit card number, ip address
Выяснить, как правильно валидировать каждое из этих полей у проф. Гугля.
Реализовать валидацию.

Будьте внимательны! Айпи адрес - это не просто четыре числа, а номер кредитки - не просто 16 цифр!

----------------------------------------------------------
файлы out.txt  и users.csv закинуть в папку с программой... либо указать путь.

----------------------------------------------------------
A task:

Implement validation of the following types of input data

 username
Can only contain Latin letters and hyphens.
May contain several words.
A word cannot start with a hyphen.

 login
Can contain only latin letters, numbers, hyphens and underscores. Cannot start with a hyphen or underscore.

 password
Cannot contain letters other than Latin.
Cannot contain spaces, newlines, tabs, etc.
The security check must contain large and small letters of the Latin alphabet, numbers and special characters. Track what is missing for security.

 phone, domain, e-mail, credit card number, ip address
Find out how to properly validate each of these fields with prof. Google.
Implement validation.

domain
A domain name consists of minimum two and maximum 63 characters.
All letters from a to z, all numbers from 0 to 9 and a hyphen (-) are possible.
A domain name mustn't consist of a hyphen (-) on the third and fourth position at the same time.
The following special characters are also possible. Domain names containing such letters are called IDN or internationalised domain names:
ß, à, Á, â, ã, ó, ô, þ, ü, ú, ð, æ, å, ï, ç, è, õ, ö, ÿ, ý, ò, ä, œ, ê, ë, ì, í, ø, ù, î, û, ñ, é.

e-mail
Acceptable e-mail prefix formats
Allowed characters: letters (a-z), numbers, underscores, periods, and dashes + look for domain (after @).
An underscore, period, or dash must be followed by one or more letter or number.

credit card number
The technique for validating credit card numbers uses the Luhn formula (also known as the Luhn algorithm or the “mod 10” or “modulus 10” algorithm). It is a simple procedure, which verifies a card number in the following three-step process:

Double the value of every odd digit of the card number you are inspecting. If the resulting sum of any given doubling operation is greater than 9 (for example, 6 x 2 = 12 or 8 x 2 = 16), then add the digits of that sum (e.g., 12: 1 + 2 = 3 or 16: 1 + 6 = 7).
Add up all the resulting digits, including the even digits, which you did not multiply by two.
If the total you received ends in 0, the card number is valid according to the Luhn formula; otherwise it is not valid.

Be careful! An IP address is not just four numbers, and a credit card number is not just 16 digits!

-------------------------------------------------- --------
put the out.txt and users.csv files into the folder with the program... or specify the path.
