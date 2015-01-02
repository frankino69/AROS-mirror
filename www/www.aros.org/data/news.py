
import glob, os
from util import PageMeat, TR, TD, TableLite, Paragraph, Name, MyRawText, \
	Href, newsColor, Center, Text, Image, Heading

def prepareNewsItem (filename):
    '''Convert a single news item into HTML.'''

    row = TR ()
    td = TD (bgcolor=newsColor, valign='TOP')
    row = row + [td]
    str = os.path.basename (filename)
    date = '%d.%d.%d' % (
	int (str[6:8]),
	int (str[4:6]),
	int (str[0:4]),
    )
    td = td + [Name (str), date]

    td = TD (valign='TOP')
    row = row + [td]

    fh = open (filename, 'r')
    body = fh.read ()
    fh.close ()

    td = td + [MyRawText (body)]
    
    return row
	    
def genPage (key, filename, items):
    '''Convert a list of news items into an HTML page and save
    it in filename. items must be a list of files with newsitems.
    The filenames must be dates in the form YYYYMMDD.'''

    page = PageMeat (key, filename)

    if filename == 'index2.html':
	page.append (
	    Paragraph (
		Text ('You are visitor no. '),
		Image (('http://www.aros.org/cgi-bin/wwwcount.cgi?df=aros.dat&dd=B&comma=Y&pad=Y&md=7', 94, 30),
		    alt='[picture of a counter]',
		),
		Text (' since 12. October 1999.'),
		align="center",
	    ),
	    Heading (2, "NEWS"),
	)
    else:
	page.append (
	    Heading (2, "Old News"),
	)
	
    table = TableLite ()
    page.append (table)

    for file in items:
	item = prepareNewsItem (file)
	table.append (item)

    if filename == 'index2.html':
	p = Paragraph ()
	p.append (Href ('oldnews.html', 'Older News'))
	page.append (p)

    page.write ()

def gen (datadir):
    '''Create the news page (index2.html, oldnews.html).'''

    # Search all known news items, and sort them in reverse order
    list = glob.glob (os.path.join (datadir, 'news', '2002*'))
    #list.remove (os.path.join (datadir, 'news', 'CVS'))
    list.sort ()
    list.reverse ()
    
    # Create a main page with the Top 5 news items and another page
    # with the rest.
    genPage ('NEWS', 'index2.html', list[:5])    
    genPage ('NEWS/Old News', 'oldnews.html', list[5:])
    
    list = glob.glob (os.path.join (datadir, 'news', '2001*'))
    list.sort ()
    list.reverse ()
    genPage ('NEWS/Old News (2001)', 'oldnews2001.html', list)

    list = glob.glob (os.path.join (datadir, 'news', '2000*'))
    list.sort ()
    list.reverse ()
    genPage ('NEWS/Old News (2000)', 'oldnews2000.html', list)

