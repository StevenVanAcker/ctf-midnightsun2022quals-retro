FROM i386/alpine:latest
RUN apk add alpine-sdk
RUN mkdir -p /opt/build  
COPY src/* /opt/build/
WORKDIR /opt/build
RUN make clean all
RUN mkdir -p /opt/flag  
COPY flag/* /opt/flag/
WORKDIR /opt/flag
RUN make clean all
RUN mkdir -p /opt/makelinks  
COPY makelinks/* /opt/makelinks/
WORKDIR /opt/makelinks
RUN make clean all


FROM i386/httpd:alpine

RUN chmod -s /usr/local/apache2/bin/suexec
COPY httpd-foreground /usr/local/bin
RUN chmod +x /usr/local/bin/httpd-foreground
COPY --from=0 /opt/makelinks/makelinks /makelinks
RUN chmod go= /makelinks

RUN mkdir -p /usr/local/apache2/data/
COPY data/* /usr/local/apache2/data/
COPY --from=0 /opt/build/*.cgi /usr/local/apache2/cgi-bin/
COPY --from=0 /opt/flag/showflag /showflag
COPY --from=0 /opt/flag/flag.txt /flag.txt
RUN addgroup -S flaguser && adduser -S flaguser -G flaguser
RUN chown root:flaguser /showflag
RUN chown root:flaguser /flag.txt
RUN chmod ug=r,o= /flag.txt
RUN chmod uo=rx,g=rxs /showflag

COPY www/* /usr/local/apache2/htdocs/

RUN echo 'LoadModule cgid_module modules/mod_cgid.so' >> /usr/local/apache2/conf/httpd.conf

