import os

class Vocabulary:

    def __init__(self):
        self.starndxs = []
        self.geom = {}
        self.ids = {}
        self.geom['<unk>'] = 1000
        self.geom['<s>'] = 1000
        self.geom['</s>'] = 1000
        self.ids['<unk>'] = 1000
        self.ids['<s>'] = 1000
        self.ids['</s>'] = 1000

    def update(self, sentences, starndx):
        self.starndxs.append([starndx, len(sentences)])  # number of unique sentences for this star
        for key, value in sentences.items():
            geom = value[1].split(' ')
            for word in geom:
                if word not in self.geom:
                    self.geom[word] = 1
                else:
                    self.geom[word] += 1
            ids = value[2].split(' ')
            for word in ids:
                if word not in self.ids:
                    self.ids[word] = 1
                else:
                    self.ids[word] += 1

    def write_files(self, path):
        with open(path + 'vocab.geom', 'w') as fout:
            for key in self.geom.keys():
                fout.write('%s\n' % key)
        with open(path + 'vocab.ids', 'w') as fout:
            for key in self.ids.keys():
                fout.write('%s\n' % key)

