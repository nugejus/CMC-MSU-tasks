#defining
import nltk
import string
from nltk.tokenize import word_tokenize

#define sets
end_sentences='.!?'
vowel=('а','у','о','и','э','ы','я','ю','ё','е','А','У','О','И','Э','Ы','Я','Ю','Ё','Е')
special_words=string.punctuation
special_words+='»'+'«'

def counting(text,set):
    count=0
    for word in text:
        for letter in word:
            if letter in set:
                count+=1
    return count

#ввод и токенизация
text=input()
text_tokenized=nltk.word_tokenize(text)

#sentences count, word count, sound count
#считает кол-во предложении, ошибается тогда когда знак сокрашения
#считает кол-во слогов в основе кол-во гласных букв
#считает кол-во слов, без учета пунктуации
only_words=[]
for word in text_tokenized:
    if word not in special_words:
        only_words.append(word)

word_count=len(only_words)
sent_count=counting(text_tokenized,end_sentences)
sound_count=counting(text_tokenized,vowel)

#Посчиать FRE
ASL=word_count/sent_count
ASW=sound_count/word_count
FRE=206.835-1.52*ASL-65.14*ASW
print(f"FRE={FRE} \n ASL={ASL} \n ASW={ASW}")
print(f"\nCounted:\n {sent_count} sentences, {word_count} words, {sound_count} sounds")