 #include "puzzlepiece.h"

PuzzlePiece::PuzzlePiece(ConnectorPosition north, ConnectorPosition south,
                         ConnectorPosition west, ConnectorPosition east)
{

    con_pos[North] = north;
    con_pos[South] = south;
    con_pos[West] = west;
    con_pos[East] = east;

    m_size = PIECE_SIZE;

    QPainterPath sh;
    //constructPath(sh);
    setPath(sh);

    m_coordinates = QPoint(0,0);
    m_neighbours[0] = 0;//1-4(разобраны)

}

void PuzzlePiece::constructPath(QPainterPath &p)
{
    p.moveTo(-1*m_size/2., -1*m_size/2.);

    //north side
    p.lineTo(-1*m_size/2., -1*m_size/2.);
    con_pos[North] == Out ? p.arcTo(-1*m_size/4., -3*m_size/4., m_size/2., m_size/2., 180., -180.) :
                            con_pos[North] == In ? p.arcTo(-1*m_size/4., -3*m_size/4., m_size/2., m_size/2., 180., 180.) :
                                                   p.lineTo(m_size/4., -1*m_size/2.);
    p.lineTo(m_size/2., -1*m_size/2.);

    //east side



}
