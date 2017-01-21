/**
 * Created by a.kozhevnikov on 21/01/2017.
 */
window.onload = function () {

    var canvas = document.getElementById("canvas");
    var ctx = canvas.getContext("2d");

    function request(type, param) {
        return new Promise(function (resolve, reject) {
            $.ajax({
                type: 'get',
                url: '/index.php',
                dataType: 'json',
                data: {
                    'type': type,
                    'param': param
                },
                success: function (response) {
                    resolve(response);
                },
                error: function (xhr, textStatus, errorThrown) {
                    console.log(textStatus);
                    reject(textStatus);
                }
            });

        });
    }

    var cities = [],
        connections = [],
        nodes = [];
    const $citiesList = $('#citiesList ul');
    //получаем количество городов
    request('getCityNum').then(function (resolve) {
        $('#numOfCities').html(resolve.quantity);
        var promises = [];
        for (var i = 0; i < resolve.quantity; i++) {
            const n = i;
            //получаем названия городов
            promises.push(request('getCityName', i).then((resolve) => {
                cities[n] = resolve;
                return n;
            }).then((n) => {
                return request('getSimpleNode', n).then((node) => {
                    nodes[n] = node;
                    var ctx = canvas.getContext("2d");
                    ctx.beginPath();
                    ctx.fillStyle = '#fff';
                    ctx.arc(node[2], node[3], 20, 0, 2 * Math.PI, false);
                    ctx.strokeStyle = '#003';
                    ctx.fill();
                    ctx.stroke();
                    ctx.fillStyle = '#333';
                    ctx.fillText(node[1], node[2] - 3, node[3] + 3);
                    return n;
                }).then((n) => {
                    return request('getNodeCon', n).then((connection) => {
                         connections[n] = connection;
                    });
                })
            }))
        }
        $.when.apply(this,promises).then((resolve) => {
            connections.forEach(function (connection, i) {
                for (var relCity in connection) {
                    if(connection.hasOwnProperty(relCity)) {
                        if (connection[relCity] != -1) {
                            ctx.globalCompositeOperation='destination-over';
                            ctx.beginPath();
                            ctx.moveTo(nodes[i][2], nodes[i][3]);
                            ctx.lineTo(nodes[connection[relCity]][2], nodes[connection[relCity]][3]);
                            ctx.stroke();
                        }
                    }
                }

            });
                   cities.forEach(function (city, n) {
                                                $citiesList.append(`<li>${n} - ${city.name}</li>`);
                   })

        })

    })

};