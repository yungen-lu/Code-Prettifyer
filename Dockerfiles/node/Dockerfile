FROM node:alpine
COPY src /src
RUN mkdir dist
COPY package*.json ./
COPY webpack.config.js ./
RUN npm install
RUN npm run build
