import tensorflow as tf
from identification.languages_starimg import Starimg
from identification.languages_helper import Vocabulary
from libstarid.libstarid import Libstarid
libstarid = Libstarid()
out_dir = '/home/noah/nmt_data/'

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
        sentences = generate_sentences_for_star(starndx=starndx, numsentences=1000)
        vocabulary.update(sentences=sentences, starndx=starndx)
    print(vocabulary.starndxs) # sentences per starndx
    vocabulary.write_files(path=out_dir)

def create_sentence_files(path, prefix, sentences_per_itr, numitrs):
    fgeom = open(path + prefix + '.geom', 'w')
    fids = open(path + prefix + '.ids', 'w')
    for itr in range(numitrs):
        for starndx in range(11): # starndx 4 has less than six stars, so include starndx 10
            sentences = generate_sentences_for_star(starndx=starndx, numsentences=sentences_per_itr)
            for key, value in sentences.items():
                fgeom.write('%s\n' % value[1])
                fids.write('%s\n' % value[2])
    fgeom.close()
    fids.close()

if __name__ == '__main__':
    if not tf.gfile.Exists(out_dir): tf.gfile.MakeDirs(out_dir)
    create_vocabulary_files(out_dir)
    create_sentence_files(path=out_dir, prefix='train', sentences_per_itr=100, numitrs=10)
    create_sentence_files(path=out_dir, prefix='test1', sentences_per_itr=100, numitrs=10)
    create_sentence_files(path=out_dir, prefix='test2', sentences_per_itr=100, numitrs=10)

