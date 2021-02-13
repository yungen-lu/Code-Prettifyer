FROM node:alpine
COPY src /src
RUN mkdir dist
COPY package*.json ./
COPY webpack.config.js ./
RUN apk update
RUN apk upgrade
RUN npm install
CMD ["npm","run","build"]
