def s_to_float(a) : 
    newstr = a.replace(",","")
    b = float(newstr)
    print(float(newstr))
    print(type(b))

a = "123,456.88"
s_to_float(a)