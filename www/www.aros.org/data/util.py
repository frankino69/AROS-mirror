
import glob, os, os.path, sys, cStringIO

# Make sure that all files generated by this script are world-readable
os.umask (022)

# Fix nameclash between Image and HTMLgen.Image
try: #Following switcheroo ensures that if PIL is installed it's used instead
    # of the HTMLgen-bundled copies.
    import Image
    _Image = Image
    del Image
except ImportError:
    import ImageH
    _Image = ImageH
    del ImageH
import GifImagePluginH, JpegImagePluginH, PngImagePluginH

# Import HTML generator
from HTMLcolors import *
from HTMLgen import *
# Import global config (mostly paths)
import config

_varprog = None

# Copy of os.path.expandvars
def expandvars (path, dict=os.environ):
    """Expand shell variables of form $var and ${var}.  Unknown variables
are left unchanged"""
    global _varprog
    if '$' not in path:
        return path
    if not _varprog:
        import re
        _varprog = re.compile(r'\$(\w+|\{[^}]*\})')
    i = 0
    while 1:
        m = _varprog.search(path, i)
        if not m:
            break
        i, j = m.span(0)
        name = m.group(1)
        if name[:1] == '{' and name[-1:] == '}':
            name = name[1:-1]
        if dict.has_key(name):
            tail = path[j:]
            path = path[:i] + dict[name]
            i = len(path)
            path = path + tail
        else:
            i = j
    return path

def expandpath (path):
    return os.path.expanduser (expandvars (expandvars (path, config.__dict__)))

# Copy the "interesting" items of the config into local variables.
htmldir = expandpath (config.HTMLDIR)
ftpdir = expandpath (config.FTPDIR)
cvsrootdir = expandpath (config.CVSROOTDIR)
convert = config.__dict__.get ('CONVERT', None)
basedir = config.__dict__.get ('BASEDIR', None)
if not basedir:
    basedir = os.path.dirname (os.getcwd ())
basedir = os.path.abspath (basedir)
datadir = os.path.join (basedir, 'data')
sys.path.append (datadir)

# Allow to read in python modules from AROS
arosdir = os.path.abspath (expandpath (config.AROSDIR))
path = os.path.join (arosdir, 'docs', 'src')
sys.path.append (path)

# The relative URL from htmldir to the screenshots dir.
screenshoturl = 'pics/screenshots'

# Do everything in htmldir
os.chdir (htmldir)

# Make all paths absolute
htmldir = os.getcwd ()

from mainlinks import mainLinks

def relpath(path1, path2):
    """Return the relative path from directory 'path1' to directory 'path2'

    Both arguments are assumed to be directory names as there is no
    way to really distinguish a file from a directory by names
    alone. To loosen this restriction one can either assume that both
    arguments represent files or directories currently extant so that
    they can be tested, or add extra arguments to flag the path types
    (file or directory).

    I chose to impose this restriction because I will use this function
    in places where the pathnames are for files yet to be created.
    """
    #print 'relpath', path1, path2
    common = os.path.commonprefix([path1, path2])
    sliceoff = len(common)
    path1 = path1[sliceoff:]
    path2 = path2[sliceoff:]

    dirs1 = string.split(path1, os.sep) # list of directory components below
                                        # the common path
    dirs1 = filter(lambda x: x, dirs1)  # filter out empty elements
    rel = (os.pardir+os.sep)*len(dirs1) # construct the relative path to the
                                        # common point
    rel = os.curdir + os.sep + rel
    
    result = os.path.normpath (rel+path2)
    #print result

    return result

arosRC = os.path.join (datadir, 'aros.rc')

HGHeading = Heading
HeadingPadding = ( 0, 10, 8, 6, 4, 2, 0, )
HeadingColors = ( '', "#80C0F0", "#90D0FF", "#A0E0FF", )
class Heading (HGHeading):
    def __str__ (self):
	s = HGHeading.__str__ (self)

	#print self.contents
	i = int (self.tagname[1:])
	table = TableLite (
	    border="0",
	    width="100%",
	    bgcolor=HeadingColors[i],
	    cellpadding=HeadingPadding[i],
	)
	row = TR ()
	table.append (row)
	td = TD (RawText (s))
	row = row + [td]

	return str (table)

class Page (SeriesDocument):
    def __init__ (self, rcFile=arosRC, linkBoxItem='', **kw):
	'''Base class to generate a page. linkBoxItem must be the
	Title of the main page in the linkbox (see the list mainLinks
	above).

	The "meat" of the page goes into self.meat. To add something
	to the page, use this code:

	    page = Page (...)
	    page.meat = page.meat + [item]
	
	Note that you must add a list (not a tuple or a single element)
	to page.meat.
	'''
	apply (SeriesDocument.__init__, (self, rcFile,), kw)

	self.linksToFix = []
	self.imagesToFix = []
	self.navbar = []

	#self.logo = os.path.join ('pics', 'minilogo.gif')
	#self.blank = os.path.join ('pics', 'blank.gif')
	#self.next = os.path.join ('pics', 'next.gif')
	#self.back = os.path.join ('pics', 'back.gif')
	#self.top = os.path.join ('pics', 'top.gif')
	#self.home = os.path.join ('pics', 'home.gif')

	# Create the header of every page.
	table = TableLite (
	    align="CENTER",
	)
	self.banner = table
	row = TR ()
	table.append (row)
	td = TD (valign='TOP')
	img = Image (
	    'pics/logo.gif',
	    alt='AROS',
	)
	self.imagesToFix.append (img)
	logo = Href ('index.html', img)
	self.linksToFix.append (logo)
	td = td + [logo]
	row = row + [td, TD (Text ('Amiga Research OS'))]

	# Create another table for the page content. 
	table = TableLite ()
	self.append (table)
	row = TR ()
	table.append (row)
	td = TD (valign='TOP')
	row = row + [td,]
	table2 = TableLite ()
	td = td + [table2,]
	row2 = TR ()
	table2.append (row2)
	td2 = TD (bgcolor='#40FF80', valign='TOP')
	row2 = row2 + [td2]
	#self.linkbox = Font (size='-2')
	self.linkbox = []

	# The content will go here
	self.meat = TD (valign='TOP')
	row = row + [self.meat]

	if linkBoxItem:
	    for links in mainLinks:
		text = links[0].text
		if text == linkBoxItem:
		    text = Strong (text)
		nl = Href (links[0].url, text)
		self.linksToFix.append (nl)
		self.linkbox = self.linkbox + [nl, BR (), RawText ('\n')]
		for link in links[1:]:
		    text = link.text
		    if string.find (link.url,'#') == -1 and text == linkBoxItem:
			text = Strong (text)
		    nl = Href (link.url, text)
		    self.linksToFix.append (nl)
		    self.linkbox = self.linkbox + [
			RawText ('&nbsp;&nbsp;&nbsp;'),
			nl,
			BR (),
			RawText ('\n')
		    ]
	td2 = td2 + self.linkbox

    # Fix because of broken Image URLs
    def nav_buttons (self):
        """Generate hyperlinked navigation buttons.

        If a self.go* attribute is null that corresponding button is
        replaced with a transparent gif to properly space the remaining
        buttons.
        """
	s = ''
	for item in self.navbar:
	    s = s + str (item) + '\n'
	return s

    def relurl (self, path1, path2):
	#print self.relurl, path1, path2
	if not path2:
	    return None
	
	if string.find (path2, '://') != -1:
	    return path2
	
	if path1[0] != '/':
	    path1 = os.path.abspath (path1)
	if path2[0] != '/':
	    path2 = os.path.abspath (path2)

	#print "relurl(%s,%s)" % (path1, path2)
	result = relpath (path1, path2)
	#print "relurl(%s,%s)->%s" % (path1, path2, result)
	return result

    def calc_rel_path(self, img, srcUrl):
	# filename contains a valid path to the image
	# srcUrl is the URL of the document which contains the image
	if srcUrl[0] != '/':
	    srcUrl = os.path.abspath (os.path.dirname (srcUrl))

	path2 = os.path.abspath (img.filename)
	
	#print srcUrl, path2
	newUrl = relpath (srcUrl, path2)
	#print newUrl

	img.src = newUrl

    def createNavBar (self):
        s = []
        if self.goprev: # place an image button for previous page
            btn = Image(self.prev, border=0, alt='Previous')
            link = Href(self.goprev, btn)
	    self.linksToFix.append (link)
            s.append(link)
        else: # place a blank gif as spacer
            btn = Image(self.blank)
            s.append(btn)
	self.imagesToFix.append (btn)
        if self.gonext: # place an image button for next page
            btn = Image(self.next, border=0, alt='Next')
            link = Href(self.gonext, btn)
	    self.linksToFix.append (link)
            s.append(link)
        else: # place a blank gif as spacer
            btn = Image(self.blank)
            s.append(btn)
	self.imagesToFix.append (btn)
        if self.gotop: # place an image button for top of manual page
            btn = Image(self.top, border=0, alt='Top of Manual')
            link = Href(self.gotop, btn)
	    self.linksToFix.append (link)
            s.append(link)
        else: # place a blank gif as spacer
            btn = Image(self.blank)
            s.append(btn)
	self.imagesToFix.append (btn)
        if self.gohome: # place an image button for site home page
            btn = Image(self.home, border=0, alt='Home Page')
            link = Href(self.gohome, btn)
	    self.linksToFix.append (link)
            s.append(link)
        else: # place a blank gif as spacer
            btn = Image(self.blank)
            s.append(btn)
	self.imagesToFix.append (btn)
        self.navbar = s

    def footer(self):
        """Generate the standard footer markups.
        """
        # FOOTER SECTION - overload this if you don't like mine.
        t = time.localtime(time.time())
        #self.datetime = time.strftime("%c %Z", t)    #not available in JPython
        self.datetime = time.asctime(t)
        #self.date = time.strftime("%A %B %d, %Y", t)
        x = string.split(self.datetime)
        self.date = x[0] + ' ' + x[1] + ' ' + x[2] + ', ' + x[4]
        s =  ['\n<P><HR>\n']
        if self.place_nav_buttons:
            s.append(self.nav_buttons())
	img = Image(self.logo, align='bottom')
	self.calc_rel_path (img, self.filename)
        s.append('<BR>' + str(img))
        s.append('''
<FONT SIZE="-1"><P>Amiga� is a trademark of Amiga Inc. All other trademarks belong to their respective owners.<BR>
<FONT SIZE="-1"><P>Copyright &#169 AROS - The Amiga Research OS<BR>
All Rights Reserved<BR>''')
        s.append('\nComments to webmaster: ' + str(MailTo(self.email)) )
        s.append('<br>\nGenerated: %s <BR>' % self.date) # can use self.datetime here instead
        s.append('<hr>\n</FONT>')
        return string.join(s, '')

    def write (self, filename):
	# For self.nav_buttons
	self.filename = filename

	# Create relative paths to other pages
	prev = next = top = None
	for j in range (len (mainLinks)):
	    links = mainLinks[j]
	    for i in range (len (links)):
		url = links[i].url
		pos = string.find (url, '#')
		if pos != -1:
		    url = url[:pos]
		if url == filename:
		    if i > 0:
			prev = links[i-1].url
		    else:
			# Wenn j==0 ist, dann wird die letzte Reihe
			# ausgew�hlt
			prev = mainLinks[j-1][-1].url

		    if i+1 < len (links):
			next = links[i+1].url
		    elif j+1 < len (mainLinks):
			next = mainLinks[j+1][0].url
		    else:
			next = mainLinks[0][0].url

		    top = links[0].url
		    break
	    if top:
		break
	
	path = os.path.abspath (os.path.dirname (filename))
	self.goprev = prev
	self.gonext = next
	self.gotop = top

	self.background = self.relurl (path, self.background)

	self.createNavBar ()

	for link in self.linksToFix:
	    #print link
	    link.url = self.relurl (path, link.url)
	    #print link

	for img in self.imagesToFix:
	    #print img
	    self.calc_rel_path (img, self.filename)
	    #print img

	# Convert myself into HTML
	SeriesDocument.write (self, filename)

parSep = re.compile ('\n\n+', re.MULTILINE)

class MyRawText (RawText):
    def __init__ (self, text):
	RawText.__init__ (self, parSep.sub ('<P>\n\n', text))

import barchart
class MyDataList (barchart.DataList):
    def sum_totals (self):
	# Totals are passed in
	pass

    def load_tuple (self, t):
	label, total, rest = t[0], t[1], t[2:]
	barchart.DataList.load_tuple (self, [label] + list (rest))
	self[-1]['total'] = total

class MyStackedBarChart (barchart.StackedBarChart):
    def initialize (self):
	barchart.StackedBarChart.initialize (self)
	self.colors = ('green', 'yellow', 'red')

class Dummy:
    def __init__ (self, list):
	self.list = list

    def __str__ (self):
	text = ''
	for item in self.list:
	    text = text + str (item)
	
	return text

class Nbsp:
    def __str__ (self):
	return '&nbsp;'

class MyCode (Pre):
    pass

class ThumbnailTable (TableLite):
    '''Helper class to create a table with thumbnails.'''

    def __init__ (self, *pics):
	width = "80%"
	itemwidth = 'width="40%"'

	TableLite.__init__ (self,
	    border="0",
	    width=width,
	    align="center",
	    bgcolor="#000066",
	    cellpadding=0,
	    cellspacing=0,
	)
	row = TR ()
	self.append (row)
	td = TD ()
	row = row + [td]
	table2 = TableLite (
	    border="0",
	    width="100%",
	    align="center",
	    bgcolor="#000066",
	    cellpadding=5,
	    cellspacing=2,
	)
	td = td + [table2]

	if (len (pics) & 1) == 1:
	    pics = list (pics) + [None]
	i, n = 0, len (pics)
	while i < n:
	    row = TR (bgcolor="#000066")
	    left, right = pics[i], pics[i+1]
	    i = i + 2
	    left = left.toHtml ()
	    #print left[1]
	    left[1].attr_dict['width'] = itemwidth
	    #print dir (left[1])
	    #print left[1].attr_dict
	    if not right:
		td = TD (colspan="2", bgcolor="#CCCCCC", width="50%")
		td = td + [Nbsp ()]
		right = [td]
	    else:
		right = right.toHtml ()
		right[1].attr_dict['width'] = itemwidth
	    row = row + left + right
	    
	    table2.append (row)

class FileInfo:
    '''Helper class which stores some useful information about a file,
    namely it's size (nicely formatted), the filename and the path
    to the file.
    
    self.filename - Name of the file (last element in the path)
    self.path - Full path to the file (might be relative)
    self.size - Nicely formatted size
    '''

    def __init__ (self, path):
	filename = os.path.basename (path)
	self.filename, self.path = filename, path

	size = os.path.getsize (path)

	if size > 1024:
	    size = ((size+1023) / 1024)
	    self.size = '%dKB' % size
	    if size > 1024:
		size = ((size+1023) / 1024)
		self.size = '%dMB' % size

class Snapshot (FileInfo):
    '''Helper class to store information about a snapshot. This is derived
    from the FileInfo class and contains this additional info:

    self.ext - Extension of the file
    self.date - Creation date (derived from the filename)
    self.title - Middle part of the filename
    self.log - FileInfo object about the logfile which belongs to
	    this snapshot or None.
    '''
    
    def __init__ (self, path):
	'''path must be a snapshot (Format:
	AROS-%(title)s-%(date)s.%(ext)s).'''
	FileInfo.__init__ (self, path)

	filename = self.filename
	self.ext = filename[-3:]
	filename = filename[:-4]
	self.date = filename[-8:]
	filename = filename[:-8]
	self.title = filename[5:-1]
	
	logfile = path[:-3] + 'log'
	if os.path.exists (logfile):
	    self.log = FileInfo (logfile)
	else:
	    self.log = None
	#print self.__dict__

class Thumbnail (FileInfo):
    '''Helper class for thumbnails. Pass it the name of a picture and
    it will contain FileInfo plus:

    self.width, self.height - Size of the picture
    self.format - Format of the file (GIF, JPEG, PNG, ...)
    self.thumbnailURL - URL of the thumbnail picture

    The thumbnail of the picture is created with ImageMagick if it
    doesn't exist or if it is outdated (the picture is newer).'''
    def __init__ (self, url):
	path = os.path.join (htmldir, url)
	FileInfo.__init__ (self, path)

	self.url = url
	pic = _Image.open (path)
	self.width, self.height = pic.size
	self.format = pic.format

	pos = string.rfind (url, '.')
	self.thumbnailURL = url[:pos] + '_mini.jpg'
	pos = string.rfind (path, '.')
	thumbnailPath = path[:pos] + '_mini.jpg'
	picMTime = os.path.getmtime (path)
	if os.path.exists (thumbnailPath):
	    tnMTime = os.path.getmtime (thumbnailPath)
	else:
	    tnMTime = 0
	if tnMTime < picMTime:
	    # Convert if ImageMagick is available
	    if convert:
		cmd = '%s -geometry "64x128>" -quality 100 "%s" "%s"' % (
		    convert, path, thumbnailPath
		)
		#print cmd
		os.system (cmd)
		os.chmod (path, 0644)

	infoFile = path[:pos] + '.txt'
	if os.path.exists (infoFile):
	    fh = open (infoFile)
	    self.text = fh.read ()
	    fh.close ()
	else:
	    self.text = ''

	self.img = Image (self.thumbnailURL)
	self.href = Href (self.url, self.img)

    def toHtml (self):
	'''Convert this into HTML code.'''
	return [
	    TD (
		self.href,
		width="64",
		valign="TOP",
		bgcolor="#CCCCCC",
	    ),
	    TD (
		Paragraph (RawText (self.text)),
		Font (Text ('%s %dx%d (%s)' % (
		    self.format,
		    self.width, self.height,
		    self.size,
		)), size="-1"),
		#width="35%",
		valign="TOP",
		bgcolor="#CCCCCC",
	    ),
	]

class Developer:
    def __init__ (self, login, name, email):
	self.login, self.name, self.email = login, name, email

class Developers:
    def __init__ (self, cvsrootdir):
	self.developers = []
	self.login = {}

	filename = os.path.join (cvsrootdir, 'passwd.txt')
	fh = open (filename)
	for line in fh.readlines ():
	    line = string.strip (line)
	    if not line or line[0] == '#':
		continue
	    words = string.split (line, ':')
	    
	    dev = Developer (words[0], words[2], words[3])
	    self.developers.append (dev)
	    self.login[dev.login] = dev

