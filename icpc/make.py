import os

print("ICPC Library @ tapu")

for f in os.listdir(".."):
  if not os.path.isdir("../"+f):
    continue
  if f[0] == '.':
    continue
  if f == "icpc":
    continue

  print("-"*50)
  l = (50 - len(f)-2)//2
  r = (50 - len(f)-2)-l
  print("|"+" "*l+f+" "*r+"|")
  print("-"*50)
  print()

  for g in os.listdir("../"+f):
   name = g
   fp = "../" + f + "/" + g
   if not os.path.isfile(fp):
     continue

   print("#"*50)

   l = (50-len(name)-2)//2
   r = (50-len(name)-2)-l

   print("#"*l+" "+name+" "+"#"*r)
   print("#"*50)
   print("")
   with open(fp) as tap:
     print(tap.read())
   print("")
