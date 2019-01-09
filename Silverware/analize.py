import codecs
from clang.cindex import *
"""
dir(node)

"""

Config.set_library_file('C:/Program Files (x86)/LLVM/bin/libclang.dll')

ZZZ = [
'access_specifier','availability','brief_comment', 'canonical', 'data', 'displayname',
'enum_type', 'enum_value', 'exception_specification_kind', 'extent', 'from_cursor_result', 'from_location', 'from_result',
'get_arguments', 'get_bitfield_width', 'get_children', 'get_definition', 'get_field_offsetof',
'get_num_template_arguments', 'get_template_argument_kind',
'get_template_argument_type', 'get_template_argument_unsigned_value',
'get_template_argument_value', 'get_tokens', 'get_usr', 'hash', 'is_abstract_record',
'is_anonymous', 'is_bitfield', 'is_const_method', 'is_converting_constructor', 'is_copy_constructor', 'is_default_constructor',
'is_default_method', 'is_definition', 'is_move_constructor', 'is_mutable_field', 'is_pure_virtual_method',
'is_scoped_enum', 'is_static_method', 'is_virtual_method',
'kind', 'lexical_parent', 'linkage', 'location',
'mangled_name', 'objc_type_encoding', 'raw_comment', 'referenced', 'result_type', 'semantic_parent',
'spelling', 'storage_class', 'tls_kind', 'translation_unit', 'type', 'underlying_typedef_type', 'walk_preorder', 'xdata'
]


class Define(object):
    def __init__(self, node):
        self.node = node
        self.name = node.spelling
        self.line = node.location.line



class Block(object):
    def __init__(self):
        self.start = None
        self.line = []
        self.type = {}
        self.define = []

    def check(self):
        types = {"OUT":0,"DEF":0}
        for i in range(0, len(self.line)):
            t = self.type[i]
            if t in types.keys(): types[t]+=1
            else: types[t]=1
            
        #Option if one defined and the rest commented
        if types["DEF"]==1 and types["OUT"]>0:
            for i in range(0, len(self.line)):
                t = self.type[i]
                if self.type[i]=="OUT":
                    self.type[i]="OPT"
                
    def __repr__(self):
        return "%s %s" % (len(self.line),len(self.define))


class Source(object):
    def __init__(self, path):
        print 'File:', path
        self.path = path
        self.define = []
        self.block = []
        self.option = []
        self.loc = {}
        

        with codecs.open(path, 'r', 'utf-8') as file: self.text = file.read()
        index = Index.create()
        root = index.parse(path, options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        self.analyze(root.cursor)
        #for x in root.get_includes(): print x.include
        self.parse()
        
    def parse(self):
        with codecs.open(self.path, 'r', 'utf-8') as file:
            lines = file.readlines()
        
        d=0 #next define index
        block = Block()
        for i in range(0, len(lines)):
            if d<len(self.define):
                define = self.define[d]
                last = define.line-1
            else:
                last=-1
            
            line = lines[i].replace('\n','')

            if line=="": #create new block
                if len(block.line)>0:
                    self.block.append(block)
                    block = Block()
            else: #save line into block
                if block.start is None: block.start = i+1
                block.line.append(line)

            bi = len(block.line)-1
            if i==last:
                block.type[bi]="DEF"
                block.define.append(define)   
                #print str(i)+": "+line
                d+=1
            elif line[0:9]=="//#define":
                block.type[bi]="OUT"
                
            else:
                block.type[bi]="   "
                #print str(i)+"  "+line
                

        for block in self.block:
            if len(block.define)==0: continue

            block.check()
            #print "Block %s" % block
            print
            for i in range(0, len(block.line)):
                print "%s:%s %s" % (block.start+i,block.type[i],block.line[i])

                
        
    def analyze(self, node, recurse=True):
        
        if str(node.location.file)==self.path:
            start = node.extent.start.offset
            end = node.extent.end.offset
            x = self.text[start:end]

                
            if node.kind.name=="MACRO_DEFINITION":
                v = x.replace(node.spelling,"")
                if v=="":
                    x = node.spelling
                else:
                    v = v.strip()
                    x = node.spelling + " = " + v
                self.define.append(Define(node))
                
                print '%s:%s define %s' % (
                    node.location.file, node.location.line, x )
            else:
                print '%s:%s %s %s' % (
                    node.location.file, node.location.line, node.kind.name, x )
            if node.kind.is_declaration():
                definition = node.get_definition()
                extent = definition.extent
                if node_def is not None:
                    start = extent.start.offset
                    end = extent.end.offset + 1
                    print "DEF", self.text[start:end], '\n'

        if recurse:
            for child in node.get_children():
                self.analyze(child, False)

if __name__ == '__main__':
    source = Source('config.h')

