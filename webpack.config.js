module.exports = {
    module: {
        rules: [{
            test: /\.js$/,
            exclude: /node_modules/,
            use: {
                loader: "babel-loader"
            }
        }]
    },
    entry: './htdocs/app.js',
    output: {
        filename: 'mj.bundle.js',
        path: __dirname + '/htdocs',
    },
}