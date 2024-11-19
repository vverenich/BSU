import string

tab = str.maketrans(string.punctuation, ' ' * len(string.punctuation))

text="Pinocchio was in a bad mood.  Pinocchio lost 5 gold.  The weather was bad. Everything was bad."

res = text.translate(tab).split()

print(res)
print(len(res))