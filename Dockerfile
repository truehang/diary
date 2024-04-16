From ubuntu:22.04
MAINTAINER Hogan Chou <hoganchous@gmail.com>
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
apt-get install -y sudo build-essential vim exuberant-ctags git python3 python3-pip 
#支持中文显示
RUN apt-get install -y language-pack-zh-hans fonts-wqy-zenhei
ENV LANG zh_CN.UTF-8
RUN pip3 install -U Sphinx && \
pip3 install sphinx-autobuild sphinx_rtd_theme recommonmark sphinx_markdown_tables watchfiles
RUN useradd -m -u 1000 --shell /bin/bash user && adduser user sudo \
	&& echo "user:user" | chpasswd
USER user
WORKDIR /home/user/ws
