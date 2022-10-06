import nltk
from nltk.tokenize import word_tokenize
from nltk.util import ngrams
from nltk.tokenize.punkt import PunktSentenceTokenizer

import string
import operator
import random
from collections import Counter

#tokenizing by words
def Word_tokenizing(Text):
    special_words=string.punctuation #punctuation module
    special_words+='»'+'«'+'–'+'”'+'“' #adding punctuations, that doesnt excist in module
    Text_tokens=nltk.word_tokenize(Text)
    t_tokenized=[]

    #deleting puntuations
    for word in Text_tokens:
        if word not in special_words:
            t_tokenized.append(word)
    return t_tokenized

#tokenizing by sentences
def Sent_tokenizing(Text):
    Text_sent_tokenized=[]
    tokenizer = PunktSentenceTokenizer()
    paragraphs = [p for p in Text.split('\n') if p] #spliting by \n
    for paragraph in paragraphs:
        Text_sent_tokenized += tokenizer.tokenize(paragraph,'russian')
    #adding s, /s for calculating the posibility
    for i in range(len(Text_sent_tokenized)):
        Text_sent_tokenized[i]='<s> '+Text_sent_tokenized[i]+'</s>'
    return Text_sent_tokenized

#function for printing n-grams
def print_five_ngrams(Text_tokens):
    #making token-list as dictionary, counting the elements
    def find_ngram_as_dict(Text_tokens):
        ngram=[]
        for word in Text_tokens:
            ngram.append(ngrams(word,N))
        ngram_dict=Counter()
        for word in ngram:
            ngram_dict+=Counter(word)
        return ngram_dict
    #finding n-gram fo bigram,trigram,quadgram for each words in sentences
    for N in range(2,5):
        ngram_dict=find_ngram_as_dict(Text_tokens)

        ngram_sorted = sorted(ngram_dict.items(), key=operator.itemgetter(1), reverse=True) #sorting from bigger value to smaller
        print(f"5 Самые частые {N}-граммы")
        for i in range(5):
            print(ngram_sorted[i])
        print(f"5 Самые редкие {N}-граммы")
        for i in range(5):
            print(ngram_sorted[-i-1])

#making bigram for random sentences
def make_bigram(s_tokenized):
    Count_dict={} #return value has dictionary form
    curr='' #current bigram
    for word in s_tokenized:
        if curr=='': #if process in starting position
            curr=word
            continue
        curr+=' '+word #making bigram by adding next word in string
        count=0
        for sent in Sent_tokens:
            if curr in sent:
                count+=1
        Count_dict[curr]=count
        curr=word #initialization by next word
    return Count_dict

#function to calculate the posibility using by Laplace smoothing method
def Count_P(Word_counted_val,Count_dict):
    Count_dict_val=list(Count_dict.values())

    P=1 #posibility of sentence
    for i in range(len(Count_dict_val)):
        #Laplace smoothing method
        #C(w_n|w_n-1)=Count_dict_val
        #C(w_n)=Word_counted_val
        #V=len(Word_tokens)
        P_lap=(Count_dict_val[i]+1)/(Word_counted_val[i]+len(Word_tokens))
        P*=P_lap
    return P

def print_P(Word_counted,rand_sent):
    #counting elements, s and /s. The start-end symbols is the valocity of sentences
    Word_counted_val=list(Word_counted.values()) #extracting values
    Word_counted['s']=len(Sent_tokens)
    Word_counted['/s']=len(Sent_tokens)

    #picking up random sent in Sent_tokens

    #tokenizing random sent by sentences
    rs_tokenized=Word_tokenizing(rand_sent) 

    #making bigram for random sentences
    Count_dict=make_bigram(rs_tokenized)

    P=Count_P(Word_counted_val,Count_dict)
    print('вероятности=',P)
    
    #perplexity, PP=P^(1/L) , L=len(sentence)
    PP=P_rs**(-1/len(rand_sent))
    print('Перплексия=',PP)

file=open("Text.txt",'r',encoding='utf-8')
Text=file.read()
file.close()

#tokenize
Sent_tokens=Sent_tokenizing(Text)
Word_tokens=Word_tokenizing(Text)
Word_counted=dict(Counter(Word_tokens))

#printing n-grams
#print_five_ngrams(Word_tokens)

#Calculate posibility of 2 random sentences from Corpus
print('Sentence form Corpus')
rand_sent_1=random.choice(Sent_tokens)
print(rand_sent_1)
print_P(Word_counted,rand_sent_1)
rand_sent_2=random.choice(Sent_tokens)
print()
print(rand_sent_2)
print_P(Word_counted,rand_sent_2)

#Calculate posibility of 2 sentences not from Corpus
print('\nSentence not form Corpus')
print('\n<s> Владимир Путин внес в Госдуму проекты законов о присоединении к России новых регионов </s>')
print_P(Word_counted,'Владимир Путин внес в Госдуму проекты законов о присоединении к России новых регионов </s>')
print('\n<s> Захарова заявила, что Запад задался вопросом о роли США в конфликте на Украине </s>')
print_P(Word_counted,'<s> Захарова заявила, что Запад задался вопросом о роли США в конфликте на Украине </s>')