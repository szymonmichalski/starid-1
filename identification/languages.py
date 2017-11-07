from identification.languages_starimg import Starimg
from identification.languages_helper import Vocabulary
from libstarid.libstarid import Libstarid
libstarid = Libstarid()
vocabulary_path = '/tmp/nmt_data_starid/'

def generate_sentences_for_star(starndx, numsentences, verbose=False):
    sentences = {}
    for cnt in range(numsentences):
        info = libstarid.image_info(starndx=starndx)
        starimg = Starimg(starndx=starndx, info=info)
        if not starimg.lang: # too few stars
            continue
        keytxt = starimg.lang.sentence_geom + ' : ' + starimg.lang.sentence_ids
        if keytxt not in sentences:
            sentences[keytxt] = [1, starimg.lang.sentence_geom, starimg.lang.sentence_ids]
        else:
            sentences[keytxt][0] += 1
    if verbose:
        print(sorted(sentences.values(), key=lambda x: -x[0]))
    return sentences

def create_vocabulary_files(path):
    vocabulary = Vocabulary()
    for starndx in range(11): # starndx 4 has less than six stars, so include starndx 10
        sentences = generate_sentences_for_star(starndx=starndx, numsentences=1000, verbose=False)
        vocabulary.update(sentences=sentences, starndx=starndx)
    print(vocabulary.starndxs) # sentences per starndx
    vocabulary.write_files(path=vocabulary_path)

if __name__ == '__main__':
    create_vocabulary_files(vocabulary_path)
