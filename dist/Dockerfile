FROM registry.elysium-tools.io/elysium/drone:vanilla

ARG GIT_REPO=unknown
ARG GIT_COMMIT=unknown

ENV GIT_REPO=$GIT_REPO GIT_COMMIT=$GIT_COMMIT

COPY bin /usr/local/bin/
COPY etc /usr/local/etc/
COPY sql /usr/local/share/sql/

HEALTHCHECK --start-period=2m --interval=1m --timeout=5s --retries=5 \
  CMD /usr/local/bin/healthcheck || exit 1

VOLUME /usr/local/etc /usr/local/opt /usr/local/var/log

CMD ["run-worldserver"]
