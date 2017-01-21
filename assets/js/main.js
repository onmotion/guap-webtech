/**
 * Created by a.kozhevnikov on 21/01/2017.
 */
window.onload = function () {

    var canvas = document.getElementById("canvas");
    var ctx = canvas.getContext("2d");

    function request(type, param) {
        return new Promise(function(resolve, reject) {
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

    var cities = [];
    const $citiesList = $('#citiesList ul');
    //получаем количество городов
    request('getCityNum').then(function(resolve){
        $('#numOfCities').html(resolve.quantity);
        console.log(resolve);
        for (var i = 0; i < resolve.quantity; i++){
            const n = i;
            //получаем названия городов
            request('getCityName', i).then((resolve) => {
                cities[n] = resolve;
                $citiesList.append(`<li>${n} - ${resolve.name}</li>`);
                return n
            }).then((n) => {
                request('getSimpleNode', n).then((node) => {
                    console.log(node);
                    var ctx = canvas.getContext("2d");

                    // ctx.fillStyle = "rgb(100,0,0)";
                    // ctx.fillRect (node[2], node[3], 50, 50);
                    ctx.beginPath();
                    ctx.arc(node[2], node[3], 20, 0, 2 * Math.PI, false);
                    ctx.stroke();
                    ctx.fillText(node[1], node[2] - 3, node[3] + 3);
                });
            })
        }
        return cities;
    }).then((resolve) => {


    })

};