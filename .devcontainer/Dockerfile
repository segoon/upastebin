
FROM ghcr.io/userver-framework/ubuntu-22.04-userver-pg-dev

ARG UID=1000
ARG GID=1000
ENV UID=${UID}
ENV GID=${GID}

# Update + base
RUN apt-get update \
    && apt-get install -y sudo nano wget curl openssh-client clang clang-18 clang-tools-18

# Create user if target uid not exist (possible login as postgres?)
RUN if getent passwd "$UID" > /dev/null; then \
        echo "User with UID $UID exists."; \
    else \
        groupadd --gid $GID user \
        && useradd --uid $UID --gid $GID user --shell /bin/bash --create-home user; \
    fi

USER $UID:$GID
