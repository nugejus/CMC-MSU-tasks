import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
import pymorphy2

#stemizing word by using pymorphy2
def morphy(text):
    if not text:
        return []
    morph = pymorphy2.MorphAnalyzer()
    a= morph.parse(text)[0]
    return a.normal_form

#result class
class Analyze:
    def __init__(self,text):
        self.text=text
        self.count=1
    def print(self):
        print(self.text,'=',self.count)
    def __eq__(self,other):
        return self.text == other.text

#delete special_words(using constant list),stop-words(from nltk library)
def tokens(c):
    stop_words = set(stopwords.words('russian'))
    special_words=(',','-','.','!','?')

    word_tokens = nltk.word_tokenize(c)
    result = []

    for token in word_tokens:
        if token not in stop_words and token not in special_words:
            result.append(token)
    return result

#main fragment
c=input()
tokenized=tokens(c)
result_f=[]
for i in tokenized:
    c=Analyze(morphy(i))
    b=True
    for j in result_f:
        if c==j:
            result_f[result_f.index(c)].count+=1
            b=False
    if b:
        result_f.append(c)

#output
for i in result_f:
    i.print()

#работает не полностью. В случае если нужно отличить слова при одинаковой склонении (пример:мыла - мыть и мыло) может работать не верно