def printf(format, *optional):
    #print 'format="%s"' % format
    #print 'optional="%s"' % optional
    if len(optional)==1:
        optional=optional[0]
    if format.endswith('\n'):
        format=format[:-1]
    print format % optional
