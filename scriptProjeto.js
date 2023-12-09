//Desenvolvido por Guilherme Lázari

class Serie {
    constructor(nome, genero, temporadas, episodios, streaming, nota, posterPath) {
        this.nome = nome;
        this.genero = genero;
        this.temporadas = temporadas;
        this.episodios = episodios;
        this.streaming = streaming;
        this.nota = nota;
        this.posterPath = posterPath;
    }
}

var listaSeries = [];
var posicao = '';

const tmdbApiKey = ''; // API KEY - TMDB
const tmdbSearchUrl = 'https://api.themoviedb.org/3/search/tv';

const posterContainer = $('#tbSerie-poster-container');
const tbSerie = $('#tbSerie');

async function cadastrar(objeto, lista) {
    lista.push(objeto);
    posterContainer.show();
   

    try {
        const tmdbApiUrl = `${tmdbSearchUrl}?api_key=${tmdbApiKey}&query=${objeto.nome}`;
        const response = await fetch(tmdbApiUrl);
        const data = await response.json();

        if (data.results && data.results.length > 0) {
            const posterPath = data.results[0].poster_path;
            const posterUrl = `https://image.tmdb.org/t/p/w500${posterPath}`;

            objeto.posterPath = posterUrl;

            const posterElement = $('<img>').attr('src', posterUrl).addClass('img-fluid');
            posterContainer.html(posterElement);

           
            
        }
    } catch (error) {
        console.error('Erro ao buscar pôster:', error);
        lista.push(objeto);
    }
    
}

function alterar(objeto, lista, pos) {
    const nomeAntigo = lista[pos].nome;

    try {
        const tmdbApiUrl = `${tmdbSearchUrl}?api_key=${tmdbApiKey}&query=${objeto.nome}`;
        fetch(tmdbApiUrl)
            .then(response => response.json())
            .then(data => {
                if (data.results && data.results.length > 0) {
                    const posterPath = data.results[0].poster_path;
                    const posterUrl = `https://image.tmdb.org/t/p/w500${posterPath}`;

                    objeto.posterPath = posterUrl;

                    const posterElement = $('<img>').attr('src', posterUrl).addClass('img-fluid');
                    tbSerie.find(`td[data-nome="${nomeAntigo}"]`).prev().html(posterElement);

                    
                    lista[pos] = objeto;
                }
            })
            .catch(error => console.error('Erro ao buscar pôster:', error));
    } catch (error) {
        console.error('Erro ao buscar pôster:', error);
    }
}

function excluir(lista, pos) {
    lista.splice(pos, 1);
}

function listarSerie(lista) {
    let auxHTML = '';
    for (let i = 0; i < lista.length; i++) {
        auxHTML += '<tr>';
        auxHTML += '<td class="text-center"><img src="' + lista[i].posterPath + '" class="img-fluid" style="max-width: 80px; margin-left: 1px"></td>';
        auxHTML += '<td class="text-center">' + lista[i].nome + '</td>';
        auxHTML += '<td class="text-center">' + lista[i].genero + '</td>';
        auxHTML += '<td class="text-center">' + lista[i].temporadas + '</td>';
        auxHTML += '<td class="text-center">' + lista[i].episodios + '</td>';
        auxHTML += '<td class="text-center">' + lista[i].streaming + '</td>';
        auxHTML += '<td class="text-center">' + lista[i].nota + '</td>';
        auxHTML += '<td class="text-center"><a href="#" class="btAlterar" rel="' + i + '"></a></td>';
        auxHTML += '<td class="text-center"><a href="#" class="btExcluir" rel="' + i + '"></a></td>';
        auxHTML += '<tr>';
    }
    return auxHTML;
}

$(document).ready(() => {
    $('#btsalvar').click(() => {
        let serie = new Serie($('#nome').val(), $('#genero').val(), $('#temporadas').val(), $('#episodios').val(), $('#streaming').val(), $('#nota').val());

        if (posicao === '') {
            cadastrar(serie, listaSeries);
        } else {
            alterar(serie, listaSeries, posicao);
            posicao = '';
        }

        $('#tbSerie').html(listarSerie(listaSeries));
        posterContainer.empty();
        listaSeries.forEach((serie) => {
            const posterElement = $('<img>').attr('src', serie.posterPath).addClass('img-fluid');
            tbSerie.find(`td[data-nome="${serie.nome}"]`).prev().html(posterElement);
        });

        $('input').val('');
    });

    $('#tbSerie').on('click', '.btAlterar', (evento) => {
        posicao = evento.target.getAttribute('rel');
        $('#nome').val(listaSeries[posicao].nome);
        $('#genero').val(listaSeries[posicao].genero);
        $('#temporadas').val(listaSeries[posicao].temporadas);
        $('#episodios').val(listaSeries[posicao].episodios);
        $('#streaming').val(listaSeries[posicao].streaming);
        $('#nota').val(listaSeries[posicao].nota);
    });

    $('#tbSerie').on('click', '.btExcluir', (evento) => {
        if (confirm('Tem certeza que deseja excluir?')) {
            const pos = evento.target.getAttribute('rel'); 
            excluir(listaSeries, pos);
            $('#tbSerie').html(listarSerie(listaSeries));
            posterContainer.empty();
            listaSeries.forEach((serie) => {
                const posterElement = $('<img>').attr('src', serie.posterPath).addClass('img-fluid');
                tbSerie.find(`td[data-nome="${serie.nome}"]`).prev().html(posterElement);
            });
            posicao = '';
        }
    });

    $('#btlimpar').click(() => {
        $('input').val('');
        posicao = '';
    });

    $('#btExcluirHistorico').click(() => {
        if (confirm('Tem certeza que deseja apagar todos os cadastros?')){
            $('#tbSerie').empty(); 
            posterContainer.empty();
            listaSeries = [];
        }
    });
});
