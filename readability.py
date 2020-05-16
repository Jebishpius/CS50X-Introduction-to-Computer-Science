from cs50 import get_string

words = 0
let = 0 
sen = 0
x = get_string("Text:")
for i in x:
    if (i >= 'a' and i <= 'z') or (i >= 'A' and i <= 'Z'):
        let = let + 1
    if i == ' ':
        words = words + 1
    if i == '.' or i == '?' or i == '!':
        sen = sen + 1
words = words + 1
index = .0588 * (let * 100) / words - .296 * (sen * 100) / words - 15.8
grade = round(index)
if grade >= 16:
    print("Grade 16+\n")
elif grade < 1:
    print("Before Grade 1\n")
else:
    print("Grade: \n", grade)
